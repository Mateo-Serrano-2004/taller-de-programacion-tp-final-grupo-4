#include "update_player_id_event.h"

#include "common/event_type.h"

Model::UpdatePlayerIDEvent::UpdatePlayerIDEvent(short_id_t new_id):
        Model::Event(Model::EventType::UPDATE_PLAYER_ID), new_id(new_id) {}

short_id_t Model::UpdatePlayerIDEvent::get_new_id() const { return new_id; }
