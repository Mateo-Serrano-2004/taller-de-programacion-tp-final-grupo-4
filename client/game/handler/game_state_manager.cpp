#include "game_state_manager.h"

#include <mutex>
#include <map>
#include <list>
#include <algorithm>
#include <memory>
#include <utility>
#include <iostream>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include "common/DTO/game_state_dto.h"
#include "common/model/player.h"

#include "controller/game_controller.h"

#include "model/game_state.h"
#include "model/rendered_player.h"

#include "render/camera.h"

Controller::GameStateManager::GameStateManager(Weak<Controller::GameController> controller):
        reference_player_id(std::nullopt),
        game_state(make_shared<Model::GameState>()),
        controller(controller) {
    SDL2pp::Point viewport_size = controller.lock()->get_renderer()->GetLogicalSize();
    game_state->camera.set_viewport_size(viewport_size.GetX(), viewport_size.GetY());
}

Model::RenderContext Controller::GameStateManager::get_render_context() {
    std::lock_guard<std::mutex> lock(mutex);
    return Model::RenderContext(
        game_state->time_left,
        game_state->get_player_by_id(reference_player_id)
    );
}

Model::FullRenderContext Controller::GameStateManager::get_full_render_context() {
    std::lock_guard<std::mutex> lock(mutex);
    return Model::FullRenderContext(
        game_state->time_left,
        game_state->get_player_by_id(reference_player_id),
        game_state->players,
        game_state->fires,
        game_state->map,
        game_state->camera
    );
}

void Controller::GameStateManager::update_player_id(short_id_t new_id) {
    std::lock_guard<std::mutex> lock(mutex);
    reference_player_id = new_id;
}

void Controller::GameStateManager::update_map(Shared<SDL2pp::Texture> new_map) {
    std::lock_guard<std::mutex> lock(mutex);
    game_state->map = new_map;
}

void Controller::GameStateManager::update(DTO::GameStateDTO&& game_state_dto) {
    auto new_game_state = make_shared<Model::GameState>();

    for (const auto& dto: game_state_dto.players) {
        auto player = make_shared<View::RenderedPlayer>(controller, std::move(dto.to_player()));
        new_game_state->players.insert({player->get_id(), player});

        if (player->is_shooting()) {
            new_game_state->fires.push_back(make_shared<View::MuzzleFireAnimation>(
                controller,
                player->get_id()
            ));
        }
    }

    new_game_state->map = game_state->map;

    std::lock_guard<std::mutex> lock(mutex);
    game_state->time_left = game_state_dto.round.time_left;
    game_state->players = new_game_state->players;

    auto ref_player = game_state->get_player_by_id(reference_player_id);
    if (ref_player) {
        auto reference_player_position = ref_player->get_position();
        game_state->camera.set_center(reference_player_position.get_x(), reference_player_position.get_y());
    }

    game_state->fires.remove_if([](Shared<View::MuzzleFireAnimation>& a) { return a->has_ended(); });
    game_state->fires.splice(game_state->fires.end(), new_game_state->fires);
}
