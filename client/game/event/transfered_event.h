#ifndef CLIENT_GAME_EVENT_TRANSFERED_EVENT_H
#define CLIENT_GAME_EVENT_TRANSFERED_EVENT_H

#include "common/event_type.h"
#include "interface/transfered.h"

#include "event.h"

namespace Model {
class TransferedEvent: public Event, public Transfered {
public:
    explicit TransferedEvent(EventType type): Event(type) {}
    virtual ~TransferedEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_TRANSFERED_EVENT_H
