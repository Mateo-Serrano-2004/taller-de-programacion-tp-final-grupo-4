#ifndef CLIENT_GAME_EVENT_LEAVE_GAME_EVENT_H
#define CLIENT_GAME_EVENT_LEAVE_GAME_EVENT_H

#include "common/DTO/event_dto.h"
#include "dto_handler/dto_creator_visitor.h"

#include "transfered_event.h"

namespace Model {
class LeaveGameEvent: public TransferedEvent {
public:
    LeaveGameEvent();

    DTO::EventDTO as_dto() override;

    ~LeaveGameEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_LEAVE_GAME_EVENT_H
