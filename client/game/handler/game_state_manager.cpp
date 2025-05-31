#include "game_state_manager.h"

#include <mutex>
#include <functional>
#include <memory>
#include <utility>

#include "common/model/player.h"
#include "common/DTO/game_state_dto.h"

short_id_t Controller::GameStateManager::get_reference_player_id() {
    return reference_player_id;
}

Model::Player& Controller::GameStateManager::get_reference_player() {
    return game_state->get_players().at(reference_player_id);
}

Controller::GameStateManager::GameStateManager(short_id_t reference_player_id) : reference_player_id(reference_player_id) {}

void Controller::GameStateManager::map_function_on_players(std::function<void(const Model::Player&)> function) {
    std::lock_guard<std::mutex> lock(mutex);
    auto& players = game_state->get_players();
    for (const auto& player : players) {
        function(player.second);
    }
}

void Controller::GameStateManager::update(DTO::GameStateDTO&& game_state_dto) {
    auto new_game_state = make_shared<Model::GameState>();

    for (DTO::PlayerDTO& player_dto: game_state_dto.players) {
        Model::Player player = player_dto_parser.parse(std::move(player_dto));
        new_game_state->register_player(std::move(player));
    }

    std::lock_guard<std::mutex> lock(mutex);
    game_state = new_game_state;
}
