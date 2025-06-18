#ifndef CLIENT_GAME_EVENT_UPDATE_PLAYER_ID_EVENT_H
#define CLIENT_GAME_EVENT_UPDATE_PLAYER_ID_EVENT_H

#include "common/definitions.h"

#include "event.h"

namespace Model {
class UpdatePlayerIDEvent: public Event {
protected:
    short_id_t new_id;

public:
    explicit UpdatePlayerIDEvent(short_id_t new_id);

    short_id_t get_new_id() const;

    ~UpdatePlayerIDEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_UPDATE_PLAYER_ID_EVENT_H
