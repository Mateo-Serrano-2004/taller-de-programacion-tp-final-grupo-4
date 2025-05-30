#include "game_state_updater.h"

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "common/definitions.h"
#include "exception/closed_window.h"
#include "model/game_state.h"

DTO::GameStateUpdater::GameStateUpdater(Model::GameState* game_state):
        game_state(game_state), reference_player_id(game_state->get_reference_player_id()) {}

void DTO::GameStateUpdater::update(DTO::GameStateDTO& game_state_dto) {
    auto new_game_state = make_shared<Model::GameState>(reference_player_id);

    for (DTO::PlayerDTO& player_dto: game_state_dto.players) {
        Model::Player player = player_dto_parser.parse(player_dto);
        new_game_state->players.insert({player.get_id(), std::move(player)});
    }

    game_state->update(new_game_state);
}
