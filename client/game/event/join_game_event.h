#ifndef CLIENT_EVENT_JOIN_GAME_EVENT_H
#define CLIENT_EVENT_JOIN_GAME_EVENT_H

#include <cstdint>
#include <string>

#include "common/DTO/event_dto.h"
#include "common/definitions.h"
#include "common/event_type.h"
#include "dto_handler/dto_creator_visitor.h"

#include "transfered_event.h"

namespace Model {
class JoinGameEvent: public TransferedEvent {
private:
    short_id_t game_id;

public:
    explicit JoinGameEvent(short_id_t game_id):
            TransferedEvent(EventType::JOIN_GAME), game_id(game_id) {}

    short_id_t get_game_id() const;

    DTO::EventDTO as_dto() override;

    ~JoinGameEvent() override = default;
};
}  // namespace Model

#endif  // CLIENT_EVENT_JOIN_GAME_EVENT_H
