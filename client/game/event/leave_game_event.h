#ifndef CLIENT_GAME_EVENT_LEAVE_GAME_EVENT_H
#define CLIENT_GAME_EVENT_LEAVE_GAME_EVENT_H

#include "event.h"

namespace Model {
    class LeaveGameEvent : public Event {
    public:
        LeaveGameEvent();

        ~LeaveGameEvent() override = default;
    };
}; // namespace Model

#endif // CLIENT_GAME_EVENT_LEAVE_GAME_EVENT_H
