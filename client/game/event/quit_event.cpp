#include "quit_event.h"

DTO::EventDTO Model::QuitEvent::as_dto() { return DTO::DTOCreatorVisitor::visit_quit_event(); }
