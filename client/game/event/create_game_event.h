#ifndef CLIENT_EVENT_CREATE_GAME_EVENT_H
#define CLIENT_EVENT_CREATE_GAME_EVENT_H

#include <string>

#include "common/DTO/event_dto.h"
#include "common/event_type.h"
#include "dto_handler/dto_creator_visitor.h"

#include "transfered_event.h"

namespace Model {
class CreateGameEvent: public TransferedEvent {
private:
    std::string party_name;
    std::string map_name;

public:
    CreateGameEvent(const std::string& party_name, const std::string& map_name):
            TransferedEvent(EventType::CREATE_GAME), party_name(party_name), map_name(map_name) {}

    std::string get_party_name() const;
    std::string get_map_name() const;

    DTO::EventDTO as_dto() override;

    ~CreateGameEvent() override = default;
};
}  // namespace Model

#endif  // CLIENT_EVENT_CREATE_GAME_EVENT_H
