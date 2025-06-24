#include "update_game_state_event.h"

#include <utility>

#include "common/event_type.h"

Model::UpdateGameStateEvent::UpdateGameStateEvent(DTO::GameStateDTO&& dto):
        Model::Event(Model::EventType::UPDATE_GAME_STATE), dto(std::move(dto)) {}

DTO::GameStateDTO& Model::UpdateGameStateEvent::get_dto() { return dto; }
