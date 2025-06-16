#include "request_games_list_event.h"

DTO::EventDTO Model::RequestGamesListEvent::as_dto() {
    return DTO::DTOCreatorVisitor::visit_request_games_list_event();
}
