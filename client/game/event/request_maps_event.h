#ifndef CLIENT_GAME_EVENT_REQUEST_MAPS_EVENT_H
#define CLIENT_GAME_EVENT_REQUEST_MAPS_EVENT_H

#include "event.h"

namespace Model {
    class RequestMapsEvent : public Event {
    public:
        RequestMapsEvent();
        ~RequestMapsEvent() override = default;
    };
};

#endif // CLIENT_GAME_EVENT_REQUEST_MAPS_EVENT_H
