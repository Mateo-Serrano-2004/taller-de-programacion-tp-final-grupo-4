#ifndef COMMON_EVENT_EVENT_TYPES_H
#define COMMON_EVENT_EVENT_TYPES_H

#include <cstdint>

namespace Model {
enum class EventType : uint8_t {
    // Game events
    MOVEMENT = 0x00,
    ROTATION = 0x01,
    DROP_WEAPON = 0x02,
    USE_WEAPON = 0x03,
    DEFUSE_BOMB = 0x04,
    SWITCH_WEAPON = 0x05,
    RELOAD_WEAPON = 0x06,
    PICK_ROLE = 0x07,
    BUY_WEAPON = 0x08,
    BUY_AMMO = 0x09,
    LEAVE_GAME = 0x0A,
    STOP_MOVEMENT = 0x0B,
    STOP_USING_WEAPON = 0x0C,
    STOP_DEFUSING_BOMB = 0x0D,

    // Lobby events
    USERNAME = 0x10,
    CREATE_GAME = 0x11,
    JOIN_GAME = 0x12,
    REQUEST_GAMES_LIST = 0x13,
    REQUEST_MAPS = 0x14,

    // System events
    QUIT = 0x20,

    // Internal client events
    SWITCH_CONTEXT = 0xA0,
    END_OF_GAME = 0xA1,
    UPDATE_PLAYER_ID = 0xA2,
    UPDATE_ROLE = 0xA3,
    GENERATE_MAP = 0xA4,
    UPDATE_GAME_STATE = 0xA5
};
};

#endif  // COMMON_EVENT_EVENT_TYPES_H
