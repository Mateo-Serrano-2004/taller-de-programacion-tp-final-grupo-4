#include "game_state_manager.h"

#include <mutex>
#include <functional>
#include <memory>
#include <utility>
#include <map>

#include <SDL2pp/Window.hh>
#include <SDL2pp/Point.hh>

#include "common/model/player.h"
#include "common/DTO/game_state_dto.h"

#include "model/game_state.h"

Controller::GameStateManager::GameStateManager(
    short_id_t reference_player_id,
    Weak<SDL2pp::Window> window
): reference_player_id(reference_player_id),
   window(window) {
    SDL2pp::Point viewport_size = window.lock()->GetSize();
    camera.set_viewport_size(viewport_size.GetX(), viewport_size.GetY());
}

View::Camera Controller::GameStateManager::get_camera() {
    return camera;
}

short_id_t Controller::GameStateManager::get_reference_player_id() const { return reference_player_id; }

void Controller::GameStateManager::map_function_on_players(
        const std::function<void(Model::Player&)>& func) {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto& [id, player]: game_state->get_players()) {
        func(player);
    }
}

void Controller::GameStateManager::call_function_on_players(
    const std::function<void(std::map<short_id_t, Model::Player>&)>& func
) {
    std::lock_guard<std::mutex> lock(mutex);
    func(game_state->get_players());
}

void Controller::GameStateManager::update_camera() {
    auto new_viewport_size = window.lock()->GetSize();
    camera.set_viewport_size(new_viewport_size.GetX(), new_viewport_size.GetY());
}

uint16_t Controller::GameStateManager::get_time_left() {
    return game_state->get_time_left();
};

void Controller::GameStateManager::update(DTO::GameStateDTO&& game_state_dto) {
    auto new_game_state = make_shared<Model::GameState>();

    for (DTO::PlayerDTO& player_dto: game_state_dto.players) {
        Model::Player player = player_dto_parser.parse(std::move(player_dto));
        new_game_state->register_player(std::move(player));
    }

    new_game_state->set_time_left(game_state_dto.time_left);

    std::lock_guard<std::mutex> lock(mutex);
    game_state = new_game_state;
    auto reference_player_position = game_state->get_player_by_id(reference_player_id).get_position();
    camera.set_center(
        reference_player_position.get_x(),
        reference_player_position.get_y()
    );
}
