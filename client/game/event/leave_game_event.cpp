#include "leave_game_event.h"

#include "common/event_type.h"

Model::LeaveGameEvent::LeaveGameEvent(): Model::TransferedEvent(Model::EventType::LEAVE_GAME) {}

DTO::EventDTO Model::LeaveGameEvent::as_dto() {
    return DTO::DTOCreatorVisitor::visit_leave_event();
}
