#ifndef CLIENT_GAME_ASSET_SOUND_ID_H
#define CLIENT_GAME_ASSET_SOUND_ID_H

#include <cstdint>

namespace Model {
enum class SoundID : uint8_t {
    GLOCK_FIRE = 0x00,
    AK47_FIRE = 0x01,
    AWP_FIRE = 0x02,
    M3_FIRE = 0x03,
    KNIFE_SLASH = 0x04,
    BOMB_EXPLOSION = 0x05,
    RELOAD_SOUND = 0x06,
    BOMB_PLANTED = 0x07,
    BOMB_DEFUSED = 0x08,
    START_ROUND_CT = 0x09,
    START_ROUND_TT = 0x0A,
    WINNER_CT = 0x0B,
    WINNER_TT = 0x0C,
    HIT_SOUND = 0x0D,
    DEATH_SOUND = 0x0E,
    NO_SOUND = 0xFF
};
};

#endif  // CLIENT_GAME_ASSET_SOUND_ID_H
