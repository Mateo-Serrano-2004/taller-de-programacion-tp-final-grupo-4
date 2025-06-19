#include "defuse_bomb_event.h"

#include "common/event_type.h"
#include "dto_handler/dto_creator_visitor.h"

Model::DefuseBombEvent::DefuseBombEvent(): Model::TransferedEvent(Model::EventType::DEFUSE_BOMB) {}

DTO::EventDTO Model::DefuseBombEvent::as_dto() {
    return DTO::DTOCreatorVisitor::visit_defuse_bomb_event();
}
