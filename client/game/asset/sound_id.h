#ifndef CLIENT_GAME_ASSET_SOUND_ID_H
#define CLIENT_GAME_ASSET_SOUND_ID_H

#include <cstdint>

namespace Model {
enum class SoundID: uint8_t {
    GLOCK_FIRE = 0x00,
    AK47_FIRE = 0x01,
    AWP_FIRE = 0x02,
    M3_FIRE = 0x03,
    BOMB_EXPLOSION = 0x04
}
};

#endif // CLIENT_GAME_ASSET_SOUND_ID_H
