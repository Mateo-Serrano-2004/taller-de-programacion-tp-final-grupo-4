#ifndef COMMON_MODEL_GAME_STATE_H
#define COMMON_MODEL_GAME_STATE_H

#include <map>
#include <vector>
#include <mutex>

#include "common/model/player.h"
#include "common/definitions.h"


namespace DTO {
class GameStateUpdater;
}

namespace Model {
class GameState {
    friend DTO::GameStateUpdater;

private:
    std::mutex mutex;
    std::map<uint8_t, Player> players;
    uint8_t reference_player_id;

public:
    explicit GameState(const uint8_t reference_player_id):
            reference_player_id(reference_player_id) {}

    std::map<uint8_t, Player>& get_players();

    uint8_t get_reference_player_id() const;
    Player& get_reference_player();

    void register_player(Player&& player);

    void update(Shared<GameState> new_game_state);

    ~GameState() = default;
};
};  // namespace Model

#endif  // COMMON_MODEL_GAME_STATE_H
