#ifndef COMMON_MODEL_GAME_STATE_H
#define COMMON_MODEL_GAME_STATE_H

#include <map>

#include "common/definitions.h"
#include "common/model/player.h"


namespace Model {
class GameState {
private:
    std::map<short_id_t, Player> players;

public:
    GameState() = default;

    std::map<short_id_t, Player>& get_players();
    void register_player(Player&& player);

    ~GameState() = default;
};
};  // namespace Model

#endif  // COMMON_MODEL_GAME_STATE_H
