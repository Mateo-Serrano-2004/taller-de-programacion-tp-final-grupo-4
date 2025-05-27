#ifndef CLIENT_GAME_EVENTS_CREATE_GAME_EVENT_H
#define CLIENT_GAME_EVENTS_CREATE_GAME_EVENT_H

#include <string>

#include "event.h"
#include "event_types.h"

namespace Model {
    class CreateGameEvent : public Event {
    private:
        std::string party_name;
        std::string map_name;

    public:
        CreateGameEvent(
            const std::string& party_name,
            const std::string& map_name
        ) : Event(EventType::MATCH_CREATION), party_name(party_name), map_name(map_name) {}

        std::string get_party_name();
        std::string get_map_name();

        ~CreateGameEvent() override = default;
    };
}

#endif // CLIENT_GAME_EVENTS_CREATE_GAME_EVENT_H
