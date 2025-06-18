#include "game_state_manager.h"

#include <mutex>
#include <functional>
#include <memory>
#include <utility>
#include <map>

#include <SDL2pp/Texture.hh>

#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Point.hh>

#include "common/model/player.h"
#include "common/DTO/game_state_dto.h"

#include "controller/game_controller.h"

#include "model/game_state.h"
#include "model/rendered_player.h"

Controller::GameStateManager::GameStateManager(Weak<Controller::GameController> controller)
: map(nullptr),
  reference_player_id(std::nullopt),
  game_state(make_shared<Model::GameState>()),
  controller(controller) {
  SDL2pp::Point viewport_size = controller.lock()->get_renderer()->GetLogicalSize();
  camera.set_viewport_size(viewport_size.GetX(), viewport_size.GetY());
}

Shared<View::RenderedPlayer> Controller::GameStateManager::get_reference_player_unsafe() {
    return game_state->get_player_by_id(reference_player_id);
}

Shared<View::RenderedPlayer> Controller::GameStateManager::get_reference_player() {
    std::lock_guard<std::mutex> lock(mutex);
    return game_state->get_player_by_id(reference_player_id);
}

void Controller::GameStateManager::call_function_on_players(
    const std::function<void(std::map<short_id_t, Shared<View::RenderedPlayer>>&)>& func
) {
    std::lock_guard<std::mutex> lock(mutex);
    func(game_state->get_players());
}

uint16_t Controller::GameStateManager::get_time_left() {
    std::lock_guard<std::mutex> lock(mutex);
    return game_state->get_time_left();
}

View::Camera Controller::GameStateManager::get_camera() {
    std::lock_guard<std::mutex> lock(mutex);
    return camera;
}

Shared<SDL2pp::Texture> Controller::GameStateManager::get_map() {
    std::lock_guard<std::mutex> lock(mutex);
    return map;
};

void Controller::GameStateManager::update_player_id(short_id_t new_id) {
    std::lock_guard<std::mutex> lock(mutex);
    reference_player_id = new_id;
}

void Controller::GameStateManager::update_map(Shared<SDL2pp::Texture> new_map) {
    std::lock_guard<std::mutex> lock(mutex);
    map = new_map;
}

void Controller::GameStateManager::update(DTO::GameStateDTO&& game_state_dto) {
    auto new_game_state = make_shared<Model::GameState>();

    for (const auto& dto: game_state_dto.players) {
        auto player = make_shared<View::RenderedPlayer>(
            controller,
            std::move(dto.to_player()),
            camera
        );
        new_game_state->register_player(player);
    }

    new_game_state->set_time_left(game_state_dto.round.time_left);

    std::lock_guard<std::mutex> lock(mutex);
    game_state = new_game_state;
    auto ref_player = game_state->get_player_by_id(reference_player_id);
    if (ref_player) {
        auto reference_player_position = ref_player->get_position();
        camera.set_center(
            reference_player_position.get_x(),
            reference_player_position.get_y()
        );
    }
}
