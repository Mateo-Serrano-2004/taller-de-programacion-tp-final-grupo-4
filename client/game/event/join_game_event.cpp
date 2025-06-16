#include "join_game_event.h"

short_id_t Model::JoinGameEvent::get_game_id() const { return game_id; }

DTO::EventDTO Model::JoinGameEvent::as_dto() {
    return DTO::DTOCreatorVisitor::visit_join_game_event(this);
}
