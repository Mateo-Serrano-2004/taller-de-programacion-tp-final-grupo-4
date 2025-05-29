#ifndef CLIENT_GAME_EVENT_REQUEST_GAMES_LIST_H
#define CLIENT_GAME_EVENT_REQUEST_GAMES_LIST_H

#include "common/event_type.h"
#include "event.h"

namespace Model {
    class RequestGamesListEvent : public Event {
    public:
        RequestGamesListEvent() : Event(EventType::REQUEST_GAMES_LIST) {}
        RequestGamesListEvent(const RequestGamesListEvent&) = default;
    };
};

#endif // CLIENT_GAME_EVENT_REQUEST_GAMES_LIST_H
