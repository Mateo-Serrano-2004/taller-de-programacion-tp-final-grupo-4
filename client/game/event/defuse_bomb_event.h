#ifndef CLIENT_GAME_EVENT_DEFUSE_BOMB_EVENT_H
#define CLIENT_GAME_EVENT_DEFUSE_BOMB_EVENT_H

#include "common/DTO/event_dto.h"

#include "transfered_event.h"

namespace Model {
class DefuseBombEvent: public TransferedEvent {
public:
    DefuseBombEvent();

    DTO::EventDTO as_dto() override;

    ~DefuseBombEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_DEFUSE_BOMB_EVENT_H
