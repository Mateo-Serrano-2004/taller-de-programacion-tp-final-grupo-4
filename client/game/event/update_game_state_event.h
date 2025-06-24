#ifndef CLIENT_GAME_EVENT_UPDATE_GAME_STATE_EVENT_H
#define CLIENT_GAME_EVENT_UPDATE_GAME_STATE_EVENT_H

#include "common/DTO/game_state_dto.h"

#include "event.h"

namespace Model {
class UpdateGameStateEvent: public Event {
protected:
    DTO::GameStateDTO dto;

public:
    explicit UpdateGameStateEvent(DTO::GameStateDTO&& dto);

    DTO::GameStateDTO& get_dto();

    ~UpdateGameStateEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_UPDATE_GAME_STATE_EVENT_H
