#ifndef CLIENT_GAME_EVENT_REQUEST_GAMES_EVENT_H
#define CLIENT_GAME_EVENT_REQUEST_GAMES_EVENT_H

#include "common/event_type.h"
#include "event.h"

namespace Model {
    class RequestGamesEvent : public Event {
    public:
        RequestGamesEvent() : Event(EventType::REQUEST_GAMES) {}
        RequestGamesEvent(const RequestGamesEvent&) = default;
    };
};

#endif // CLIENT_GAME_EVENT_REQUEST_GAMES_H
