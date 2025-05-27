#ifndef COMMON_MODEL_GAME_STATE_H
#define COMMON_MODEL_GAME_STATE_H

#include <map>
#include <mutex>
#include <iostream>

#include "common/definitions.h"
#include "player.h"

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
        GameState(const uint8_t reference_player_id)
        : reference_player_id(reference_player_id) {
            std::cout << reference_player_id;
        }

        std::map<uint8_t, Player>& get_players();

        uint8_t get_reference_player_id() const;
        Player& get_reference_player();

        void register_player(Player&& player);
    
        void update(Shared<GameState> new_game_state);

        ~GameState() = default;
    };
};

#endif // COMMON_MODEL_GAME_STATE_H
