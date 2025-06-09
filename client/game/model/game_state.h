#ifndef COMMON_MODEL_GAME_STATE_H
#define COMMON_MODEL_GAME_STATE_H

#include <map>

#include "common/definitions.h"

namespace View {
class RenderedPlayer;
};

namespace Model {
class GameState {
private:
    std::map<short_id_t, Shared<View::RenderedPlayer>> players;
    uint16_t time_left;

public:
    GameState();

    std::map<short_id_t, Shared<View::RenderedPlayer>>& get_players();
    Shared<View::RenderedPlayer> get_player_by_id(short_id_t id);
    void register_player(Shared<View::RenderedPlayer> player);

    void set_time_left(uint16_t new_time_left);
    uint16_t get_time_left() const;

    ~GameState() = default;
};
};  // namespace Model

#endif  // COMMON_MODEL_GAME_STATE_H
