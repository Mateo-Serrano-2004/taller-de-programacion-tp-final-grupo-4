#ifndef CLIENT_GAME_EVENT_REQUEST_GAMES_LIST_EVENT_H
#define CLIENT_GAME_EVENT_REQUEST_GAMES_LIST_EVENT_H

#include "common/DTO/event_dto.h"
#include "common/event_type.h"
#include "dto_handler/dto_creator_visitor.h"

#include "transfered_event.h"

namespace Model {
class RequestGamesListEvent: public TransferedEvent {
public:
    RequestGamesListEvent(): TransferedEvent(EventType::REQUEST_GAMES_LIST) {}

    DTO::EventDTO as_dto() override;

    RequestGamesListEvent(const RequestGamesListEvent&) = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_REQUEST_GAMES_LIST_EVENT_H
