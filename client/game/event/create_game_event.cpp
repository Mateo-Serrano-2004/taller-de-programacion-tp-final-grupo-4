#include "create_game_event.h"

#include <string>

std::string Model::CreateGameEvent::get_party_name() const { return party_name; }

std::string Model::CreateGameEvent::get_map_name() const { return map_name; }

DTO::EventDTO Model::CreateGameEvent::as_dto() {
    return DTO::DTOCreatorVisitor::visit_create_game_event(this);
}
