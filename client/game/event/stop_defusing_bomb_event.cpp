#include "stop_defusing_bomb_event.h"

#include "common/event_type.h"
#include "dto_handler/dto_creator_visitor.h"

Model::StopDefusingBombEvent::StopDefusingBombEvent():
        Model::TransferedEvent(Model::EventType::STOP_DEFUSING_BOMB) {}

DTO::EventDTO Model::StopDefusingBombEvent::as_dto() {
    return DTO::DTOCreatorVisitor::visit_stop_defusing_bomb_event();
}
