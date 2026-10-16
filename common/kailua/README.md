# Common Kailua SDM ABI profile

Peridot selects `qtidisplay.common_kailua_sdm` because its QCOM common display extension is the LA.VENDOR.13.2.6 KAILUA cohort. The default SDM implementation remains unchanged for devices that do not select this profile.

The pinned SDM source and headers are recorded with their upstream commit and file hashes in `UPSTREAM.json`. Keep the private types and interfaces together: changing only `HWPipeCaps` leaves additional resource/strategy virtual methods, layer layouts, CWB ownership and nested types incompatible.

The observed device failure is an uncaught vector length exception from `HWResourceInfo::operator=` inside the common extension. The binary reads `hw_pipes` at offset `0xd8` and advances `HWPipeCaps` by `0x48`; the 8650 source adds a UCSC map, changing the element stride. `abi_contract.cpp` makes the two observed requirements compile-time assertions and retains further layout values in `.qtidisplay_abi` for artifact verification.

This profile builds the pinned SDM core, DAL and utility sources, and exports the same pinned headers to their source consumers. The current AIDL composer, gralloc and DRM kernel-facing components stay in use. Composer adaptations are confined to the source boundary: unsupported newer operations return unsupported, and front-buffer layers use client composition. The source-owned external null-display adapter does not change the extension interfaces. Private common structs and virtual interfaces must not gain fields or methods to satisfy newer composer callers.

The existing default 8650 framebuffer compatibility entry points remain available for the default profile. The Kailua profile builds its original framebuffer definitions coherently instead.

Compilation and symbol resolution are necessary checks, not proof of runtime private ABI compatibility. A device boot must pass SDM property/resource initialization and complete frame presentation without repeating the captured exception. Follow up with modeset, suspend/resume, CWB, color and fingerprint validation.
