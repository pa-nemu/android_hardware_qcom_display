// Compile-time contract with the common LA.VENDOR.13.2.6 KAILUA extension.
// Values are independently corroborated by the shipped extension's code.
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <private/hw_info_types.h>

#if defined(__aarch64__)
static_assert(sizeof(sdm::HWPipeCaps) == 0x48,
              "Common extension iterates HWPipeCaps in 72-byte steps");
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-offsetof"
static_assert(offsetof(sdm::HWResourceInfo, hw_pipes) == 0xd8,
              "Common extension reads the hardware pipe vector at offset 0xd8");
static_assert(std::is_same<decltype(sdm::HWLayersInfo::hw_cwb_config), sdm::CwbConfig*>::value,
              "Common extension uses non-owning CWB configuration pointers");
__attribute__((used, retain, section(".qtidisplay_abi")))
static const uint64_t kKailuaAbiContract[] = {
    0x4b41494c55413100ULL, 1,
    sizeof(sdm::HWPipeCaps), offsetof(sdm::HWResourceInfo, hw_pipes),
    sizeof(sdm::HWResourceInfo), sizeof(sdm::HWPipeInfo),
    sizeof(sdm::HWLayerConfig), sizeof(sdm::HWLayersInfo),
    sizeof(sdm::HWPanelInfo), sizeof(sdm::LayerBuffer),
};
#pragma clang diagnostic pop
#endif
