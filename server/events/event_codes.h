#ifndef EVENT_CODES_H
#define EVENT_CODES_H

enum EventGameCodes {
    MOVEMENT = 0x00,
    ROTATION = 0x01,
    DROP_WEAPON = 0x02,
    USE_WEAPON = 0x03,
    DEFUSE_BOMB = 0x04,
    SWITCH_WEAPON = 0x05,
    RELOAD_WEAPON = 0x06,
    SELECT_SIDE_AND_MODEL = 0x07,
    BUY = 0x08,
    BUY_AMMO = 0x09,
    LEAVE_GAME = 0x0A,
};

enum EventLobbyCodes {
    SEND_USERNAME = 0x10,
    CREATE_GAME = 0x11,
    JOIN_GAME = 0x12,
    LIST_GAMES = 0x13,
    MAP_REQUEST = 0x14,
};

#endif  // EVENT_CODES_H
