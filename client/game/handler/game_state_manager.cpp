#include "game_state_manager.h"

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <utility>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include "animation/muzzle_fire_animation.h"
#include "animation/progress_bar_animation.h"
#include "animation/winner_team_message_animation.h"
#include "common/DTO/game_state_dto.h"
#include "common/model/player.h"
#include "controller/game_controller.h"
#include "model/game_state.h"
#include "model/rendered_player.h"
#include "render/camera.h"
#include "sound/sound_effect.h"

Controller::GameStateManager::GameStateManager(Weak<Controller::GameController> controller):
        game_state(make_shared<Model::GameState>()), controller(controller) {
    SDL2pp::Point viewport_size = controller.lock()->get_renderer()->GetLogicalSize();
    game_state->camera.set_viewport_size(viewport_size.GetX(), viewport_size.GetY());
}

Model::GameState Controller::GameStateManager::get_game_state() {
    std::lock_guard<std::mutex> lock(mutex);
    return *game_state;
}

void Controller::GameStateManager::update_player_id(short_id_t new_id) {
    std::lock_guard<std::mutex> lock(mutex);
    game_state->reference_player_id = new_id;
}

void Controller::GameStateManager::update_map(Shared<SDL2pp::Texture> new_map) {
    std::lock_guard<std::mutex> lock(mutex);
    game_state->map = new_map;
}

void Controller::GameStateManager::update(DTO::GameStateDTO& game_state_dto) {
    auto new_game_state = make_shared<Model::GameState>();

    for (const auto& dto: game_state_dto.players) {
        auto player = make_shared<View::RenderedPlayer>(controller, std::move(dto.to_player()));
        new_game_state->players.insert({player->get_id(), player});

        if (player->is_shooting()) {
            auto weapon_id = player->get_current_weapon()->get_weapon_id();
            if (weapon_id != Model::WeaponID::KNIFE && weapon_id != Model::WeaponID::BOMB) {
                new_game_state->fires.push_back(
                    make_shared<View::MuzzleFireAnimation>(
                        controller, player->get_id()
                    )
                );
            }
            if (weapon_id != Model::WeaponID::BOMB) {
                new_game_state->shot_sounds.push_back(
                    make_shared<View::SoundEffect>(
                        controller,
                        player->get_id(),
                        player->get_current_weapon()->get_weapon_id()
                    )
                );
            }
        }
    }

    std::lock_guard<std::mutex> lock(mutex);
    game_state->players = new_game_state->players;
    game_state->fires.remove_if(
            [](Shared<View::MuzzleFireAnimation>& a) { return a->has_ended(); });
    game_state->fires.splice(game_state->fires.end(), new_game_state->fires);
    game_state->shot_sounds.remove_if(
        [](Shared<View::SoundEffect>& sf) { return sf->has_ended(); }
    );
    game_state->shot_sounds.splice(game_state->shot_sounds.end(), new_game_state->shot_sounds);

    game_state->time_left = game_state_dto.round.time_left;
    if (game_state_dto.round.bomb_planted && !game_state->bomb_position.has_value()) {
        auto pos = game_state_dto.round.bomb_position;
        game_state->bomb_position = SDL2pp::Point(pos.get_x(), pos.get_y());
    }
    if (game_state_dto.round.bomb_defused || game_state_dto.round.state != RoundState::Active) {
        game_state->bomb_position = std::nullopt;
    }
    auto ref_player = game_state->get_reference_player();
    if (ref_player) {
        auto reference_player_position = ref_player->get_position();
        game_state->camera.set_center(reference_player_position.get_x(),
                                      reference_player_position.get_y());
        if (!game_state->bomb_defusing && ref_player->is_defusing()) {
            game_state->bomb_defusing = make_shared<View::ProgressBarAnimation>(controller);
        } else if (!ref_player->is_defusing()) {
            game_state->bomb_defusing = nullptr;
        }
    }
    game_state->defusing_progress = game_state_dto.round.defusing_progress;
    if (!(game_state->bomb_position.has_value()) && game_state_dto.round.bomb_planted) {
        game_state->bomb_position = SDL2pp::Point();
        game_state->bomb_position.value().SetX(game_state_dto.round.bomb_position.get_x());
        game_state->bomb_position.value().SetX(game_state_dto.round.bomb_position.get_y());
    }
    game_state->first_team_victories = game_state_dto.ct_rounds_won;
    game_state->second_team_victories = game_state_dto.tt_rounds_won;
    game_state->round_winner = game_state_dto.round.winner;
    game_state->game_winner = game_state_dto.winner;

    if (game_state->winner_message && game_state->winner_message->has_ended())
        game_state->winner_message = nullptr;

    if (game_state_dto.round.ended && game_state->round_state == RoundState::Active) {
        game_state->winner_message = make_shared<View::WinnerTeamMessageAnimation>(
            controller, game_state->round_winner
        );
    }

    game_state->round_state = game_state_dto.round.state;
}
