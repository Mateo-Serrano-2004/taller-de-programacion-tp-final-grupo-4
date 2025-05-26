#ifndef CLIENT_GAME_EVENT_EVENT_TYPES_H
#define CLIENT_GAME_EVENT_EVENT_TYPES_H

namespace Model {
    enum EventType {
        MOVEMENT = 0x00,
        ROTATION = 0x01,
        QUIT = 0x30
    };
};

#endif // CLIENT_GAME_EVENT_EVENT_TYPES_H
