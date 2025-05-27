#include "game_state_updater.h"

#include <vector>

#include "common/definitions.h"
#include "common/model/game_state.h"

DTO::GameStateUpdater::GameStateUpdater(Model::GameState* game_state)
: game_state(game_state), reference_player_id(game_state->get_reference_player_id()) {}

Shared<Model::GameState> DTO::GameStateUpdater::parse(MatchDTO&& match_dto) {
    auto new_game_state = std::make_shared<Model::GameState>(reference_player_id);

    for (Player& player : match_dto.players) {
        new_game_state->players.insert({ player.get_id(), std::move(player) });
    }

    game_state->update(new_game_state);
}
