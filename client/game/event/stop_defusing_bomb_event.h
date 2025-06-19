#ifndef CLIENT_GAME_EVENT_STOP_DEFUSING_BOMB_EVENT_H
#define CLIENT_GAME_EVENT_STOP_DEFUSING_BOMB_EVENT_H

#include "common/DTO/event_dto.h"

#include "transfered_event.h"

namespace Model {
class StopDefusingBombEvent: public TransferedEvent {
public:
    StopDefusingBombEvent();

    DTO::EventDTO as_dto() override;

    ~StopDefusingBombEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_STOP_DEFUSING_BOMB_EVENT_H
