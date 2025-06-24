#ifndef COMMON_DTO_CONFIG_DTO_H
#define COMMON_DTO_CONFIG_DTO_H

#include <cstdint>

namespace DTO {
struct ConfigDTO {
public:
    uint16_t width;
    uint16_t height;
    uint8_t opacity;
    uint16_t angle;
    uint16_t ratio;

    ConfigDTO(): width(0), height(0), opacity(0), angle(0), ratio(0) {}
    ConfigDTO(uint16_t width, uint16_t height, uint8_t opacity, uint16_t angle, uint16_t ratio):
            width(width), height(height), opacity(opacity), angle(angle), ratio(ratio) {}
    ConfigDTO(const ConfigDTO&) = default;
};
}  // namespace DTO

#endif  // COMMON_DTO_GAME_STATE_DTO_H
