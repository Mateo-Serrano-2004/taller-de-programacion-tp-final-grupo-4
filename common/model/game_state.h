#ifndef CLIENT_GAME_MODEL_GAME_STATE_H
#define CLIENT_GAME_MODEL_GAME_STATE_H

#include <vector>
#include <mutex>

#include "player.h"

namespace Model {
    class GameState {
    private:
        std::mutex mutex;
        std::vector<Player> players;
        size_t reference_player_index;

    public:
        GameState() : reference_player_index(0) {}

        std::vector<Player>& get_players();
        Player& get_reference_player();
        void register_player(Player&& player);

        ~GameState() = default;
    };
};

#endif // CLIENT_GAME_MODEL_GAME_STATE_H
