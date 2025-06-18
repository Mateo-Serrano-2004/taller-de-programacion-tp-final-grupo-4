#ifndef CLIENT_GAME_EVENT_END_OF_GAME_EVENT_H
#define CLIENT_GAME_EVENT_END_OF_GAME_EVENT_H

#include "common/DTO/event_dto.h"

#include "event.h"

namespace Model {
class EndOfGameEvent: public Event {
public:
    EndOfGameEvent();

    ~EndOfGameEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_END_OF_GAME_EVENT_H
