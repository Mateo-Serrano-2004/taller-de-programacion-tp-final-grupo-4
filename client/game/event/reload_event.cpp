#include "reload_event.h"

#include "common/event_type.h"
#include "dto_handler/dto_creator_visitor.h"

Model::ReloadEvent::ReloadEvent(): Model::TransferedEvent(Model::EventType::RELOAD_WEAPON) {}

DTO::EventDTO Model::ReloadEvent::as_dto() { return DTO::DTOCreatorVisitor::visit_reload_event(); }
