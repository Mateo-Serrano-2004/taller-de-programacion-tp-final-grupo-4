#ifndef CLIENT_GAME_EVENT_INITIALIZE_GAME_STATE_EVENT_H
#define CLIENT_GAME_EVENT_INITIALIZE_GAME_STATE_EVENT_H

#include "common/definitions.h"

#include "event.h"

namespace Model {
class InitializeGameStateEvent: public Event {
protected:
    short_id_t player_id;

public:
    InitializeGameStateEvent(short_id_t player_id);

    short_id_t get_player_id() const;

    ~InitializeGameStateEvent() override = default;
};
};

#endif // CLIENT_GAME_EVENT_INITIALIZE_GAME_STATE_EVENT_H
