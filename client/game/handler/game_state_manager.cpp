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
#include "model/rendered_player.h"

void Controller::GameStateManager::add_player_shooting(Shared<View::RenderedPlayer> player) {
    pending_weapon_usages.push_back(player);
}

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

Shared<View::RenderedPlayer> Controller::GameStateManager::get_reference_player() {
    std::lock_guard<std::mutex> lock(mutex);
    return game_state->get_player_by_id(reference_player_id);
}

void Controller::GameStateManager::update_player_sprite(Model::TextureID texture_id) {
    std::lock_guard<std::mutex> lock(mutex);
    game_state->get_player_by_id(reference_player_id)->set_sprite_id(texture_id);
}

void Controller::GameStateManager::map_function_on_players(
        const std::function<void(Shared<View::RenderedPlayer>&)>& func) {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto& [id, player]: game_state->get_players()) {
        func(player);
    }
}

void Controller::GameStateManager::call_function_on_players(
    const std::function<void(std::map<short_id_t, Shared<View::RenderedPlayer>>&)>& func
) {
    std::lock_guard<std::mutex> lock(mutex);
    func(game_state->get_players());
}

void Controller::GameStateManager::map_function_on_pending_weapon_usages(
        const std::function<void(Shared<View::RenderedPlayer>&)>& func) {
    for (auto& player: pending_weapon_usages) {
        func(player);
    }
    pending_weapon_usages.clear();
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

    for (const auto& dto: game_state_dto.players) {
        auto player = make_shared<View::RenderedPlayer>(std::move(dto.to_player()));
        player->set_sprite_id(
            enum_translator.get_texture_from_role(player->get_role_id())
        );
        player->set_weapon_sprite_id(
            enum_translator.get_texture_from_weapon(player->get_current_weapon()->get_weapon_id())
        );
        new_game_state->register_player(player);
        if (player->is_shooting()) add_player_shooting(player);
    }

    new_game_state->set_time_left(0);

    std::lock_guard<std::mutex> lock(mutex);
    game_state = new_game_state;
    auto reference_player_position = game_state->get_player_by_id(reference_player_id)->get_position();
    camera.set_center(
        reference_player_position.get_x(),
        reference_player_position.get_y()
    );
}
