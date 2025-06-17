#include "initialize_game_state_event.h"

#include "common/event_type.h"

Model::InitializeGameStateEvent::InitializeGameStateEvent(short_id_t player_id)
: Model::Event(Model::EventType::INITIALIZE_GAME_STATE), player_id(player_id) {}

short_id_t Model::InitializeGameStateEvent::get_player_id() const { return player_id; }
