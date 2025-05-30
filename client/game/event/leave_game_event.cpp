#include "leave_game_event.h"

#include "common/event_type.h"

Model::LeaveGameEvent::LeaveGameEvent() : Model::Event(Model::EventType::LEAVE_GAME) {}
