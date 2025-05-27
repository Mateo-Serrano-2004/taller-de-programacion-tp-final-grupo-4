#include "game_state_updater.h"

#include <vector>
#include <iostream>

#include "common/definitions.h"
#include "common/model/game_state.h"
#include "exception/closed_window.h"

DTO::GameStateUpdater::GameStateUpdater(Model::GameState* game_state)
: game_state(game_state), reference_player_id(game_state->get_reference_player_id()) {}

void DTO::GameStateUpdater::update(MatchDTO&& match_dto) {
    auto new_game_state = std::make_shared<Model::GameState>(reference_player_id);

    
    for (PlayerDTO& player_dto : match_dto.players) {
        Model::Player player = player_dto_parser.parse(player_dto);
        std::cout << player.get_x() << " | " << player.get_y() << "\n";
        new_game_state->players.insert({ player.get_id(), std::move(player) });
    }

    game_state->update(new_game_state);
}
