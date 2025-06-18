#ifndef CLIENT_GAME_EVENT_REQUEST_MAPS_EVENT_H
#define CLIENT_GAME_EVENT_REQUEST_MAPS_EVENT_H

#include "common/DTO/event_dto.h"
#include "common/event_type.h"
#include "dto_handler/dto_creator_visitor.h"

#include "transfered_event.h"

namespace Model {
class RequestMapsEvent: public TransferedEvent {
public:
    RequestMapsEvent(): TransferedEvent(EventType::REQUEST_MAPS) {}

    DTO::EventDTO as_dto() override;

    ~RequestMapsEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_REQUEST_MAPS_EVENT_H
