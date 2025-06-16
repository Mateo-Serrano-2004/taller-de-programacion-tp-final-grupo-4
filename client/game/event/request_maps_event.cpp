#include "request_maps_event.h"

DTO::EventDTO Model::RequestMapsEvent::as_dto() {
    return DTO::DTOCreatorVisitor::visit_request_maps_event();
}
