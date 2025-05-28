#ifndef COMMON_EVENT_CREATE_GAME_EVENT_H
#define COMMON_EVENT_CREATE_GAME_EVENT_H

#include <string>

#include "event.h"
#include "event_type.h"

namespace Model {
    class CreateGameEvent : public Event {
    private:
        std::string party_name;
        std::string map_name;

    public:
        CreateGameEvent(
            const std::string& party_name,
            const std::string& map_name
        ) : Event(EventType::CREATE_GAME), party_name(party_name), map_name(map_name) {}

        std::string get_party_name() const;
        std::string get_map_name() const;

        ~CreateGameEvent() override = default;
    };
}

#endif // COMMON_EVENT_CREATE_GAME_EVENT_H
