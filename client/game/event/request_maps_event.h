#ifndef CLIENT_GAME_EVENT_REQUEST_MAPS_EVENT_H
#define CLIENT_GAME_EVENT_REQUEST_MAPS_EVENT_H

#include "common/event_type.h"
#include "event.h"

namespace Model {
    class RequestMapsEvent : public Event {
    public:
        RequestMapsEvent() : Event(EventType::REQUEST_MAPS) {}
        ~RequestMapsEvent() override = default;
    };
};

#endif // CLIENT_GAME_EVENT_REQUEST_MAPS_EVENT_H
