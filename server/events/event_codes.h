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
    BUY = 0x10,
    BUY_AMMO = 0x11,
    LEAVE_GAME = 0x20,
};

enum EventLobbyCodes {
    SEND_USERNAME = 0x0A,
    CREATE_GAME = 0x0B,
    JOIN_GAME = 0x0C,
    LIST_GAMES = 0x0D,
    MAP_REQUEST = 0x0E,
};

#endif  // EVENT_CODES_H
