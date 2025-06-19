#ifndef CLIENT_GAME_EVENT_RELOAD_EVENT_H
#define CLIENT_GAME_EVENT_RELOAD_EVENT_H

#include "common/DTO/event_dto.h"

#include "transfered_event.h"

namespace Model {
class ReloadEvent: public TransferedEvent {
public:
    ReloadEvent();

    DTO::EventDTO as_dto() override;

    ~ReloadEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_RELOAD_EVENT_H
