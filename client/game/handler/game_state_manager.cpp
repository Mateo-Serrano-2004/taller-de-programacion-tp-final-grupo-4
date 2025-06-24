#include "game_state_manager.h"

#include <algorithm>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <utility>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include "animation/bomb_explosion_animation.h"
#include "animation/muzzle_fire_animation.h"
#include "animation/progress_bar_animation.h"
#include "animation/winner_team_message_animation.h"
#include "asset/sound_id.h"
#include "common/DTO/game_state_dto.h"
#include "common/model/player.h"
#include "controller/game_controller.h"
#include "model/game_state.h"
#include "model/rendered_player.h"
#include "render/camera.h"
#include "sound/shot_sound.h"

void Controller::GameStateManager::load_shot_sound(const Shared<Model::GameState>& new_game_state,
                                                   const Shared<View::RenderedPlayer>& player) {
    if (!player->is_shooting())
        return;
    auto weapon_id = player->get_current_weapon()->get_weapon_id();
    if (weapon_id != Model::WeaponID::BOMB) {
        new_game_state->sound_effects.push_back(make_shared<View::ShotSound>(
                controller, player->get_current_weapon()->get_weapon_id(), player->get_id()));
    }
}

void Controller::GameStateManager::load_reload_sound(const Shared<Model::GameState>& new_game_state,
                                                     const Shared<View::RenderedPlayer>& player) {
    if (!player->is_reloading())
        return;
    new_game_state->sound_effects.push_back(make_shared<View::TrackingSoundEffect>(
            controller, Model::SoundID::RELOAD_SOUND, player->get_id()));
}

void Controller::GameStateManager::load_bomb_explosion(const DTO::GameStateDTO& dto) {
    if (game_state->bomb_explosion && game_state->bomb_explosion->has_ended())
        game_state->bomb_explosion = nullptr;
    if (game_state->bomb_explosion_sound && game_state->bomb_explosion_sound->has_ended())
        game_state->bomb_explosion_sound = nullptr;
    if (dto.round.state == RoundState::PostRound && dto.round.bomb_planted &&
        !dto.round.bomb_defused && game_state->bomb_position.has_value() &&
        game_state->round_state == RoundState::Active) {
        game_state->bomb_explosion = make_shared<View::BombExplosionAnimation>(
                controller, game_state->bomb_position.value());
        game_state->bomb_explosion_sound =
                make_shared<View::DistancedSoundEffect>(controller, Model::SoundID::BOMB_EXPLOSION);
    }
}

void Controller::GameStateManager::load_start_round_sound(
        const DTO::GameStateDTO& dto, const Shared<View::RenderedPlayer>& player) {
    if (game_state->start_round_radio && game_state->start_round_radio->has_ended())
        game_state->start_round_radio = nullptr;
    if (dto.round.state == RoundState::Active && game_state->round_state == RoundState::Buying) {
        if (player->get_team() == Model::TeamID::CT) {
            game_state->start_round_radio =
                    make_shared<View::SoundEffect>(controller, Model::SoundID::START_ROUND_CT);
        } else {
            game_state->start_round_radio =
                    make_shared<View::SoundEffect>(controller, Model::SoundID::START_ROUND_TT);
        }
    }
}

void Controller::GameStateManager::load_bomb_state_sound(const DTO::GameStateDTO& dto) {
    if (game_state->bomb_state_sound && game_state->bomb_state_sound->has_ended())
        game_state->bomb_state_sound = nullptr;
    if (dto.round.bomb_defused && !game_state->bomb_defused) {
        game_state->bomb_state_sound =
                make_shared<View::SoundEffect>(controller, Model::SoundID::BOMB_DEFUSED);
    }
    if (dto.round.bomb_planted && !game_state->bomb_planted) {
        game_state->bomb_state_sound =
                make_shared<View::SoundEffect>(controller, Model::SoundID::BOMB_PLANTED);
    }
}

void Controller::GameStateManager::load_hit_sound(const Shared<Model::GameState>& new_game_state) {
    for (const auto& player: new_game_state->players) {
        if (player.second->get_has_hit()) {
            Model::SoundID id;
            if (player.second->get_health())
                id = Model::SoundID::HIT_SOUND;
            else
                id = Model::SoundID::DEATH_SOUND;

            new_game_state->sound_effects.push_back(make_shared<View::TrackingSoundEffect>(
                    controller, id, player.second->get_id()));
        }
    }
}

void Controller::GameStateManager::winner_sound(const DTO::GameStateDTO& dto) {
    if (game_state->winner_sound && game_state->winner_sound->has_ended())
        game_state->winner_sound = nullptr;
    if (dto.winner == Model::TeamID::CT && game_state->game_winner == Model::TeamID::NONE) {
        game_state->winner_sound =
                make_shared<View::SoundEffect>(controller, Model::SoundID::WINNER_CT);
    } else if (dto.winner == Model::TeamID::TT && game_state->game_winner == Model::TeamID::NONE) {
        game_state->winner_sound =
                make_shared<View::SoundEffect>(controller, Model::SoundID::WINNER_TT);
    }
}

void Controller::GameStateManager::load_animation(const Shared<Model::GameState>& new_game_state,
                                                  const Shared<View::RenderedPlayer>& player) {
    if (!player->is_shooting())
        return;
    auto weapon_id = player->get_current_weapon()->get_weapon_id();
    if (weapon_id != Model::WeaponID::KNIFE && weapon_id != Model::WeaponID::BOMB) {
        new_game_state->fires.push_back(
                make_shared<View::MuzzleFireAnimation>(controller, player->get_id()));
    }
}

void Controller::GameStateManager::update_dropped_weapons(const DTO::GameStateDTO& dto) {
    game_state->dropped_weapons.clear();
    for (auto& weapon: dto.round.dropped_weapons) {
        game_state->dropped_weapons.push_back(make_shared<DTO::DropWeaponDTO>(weapon));
    }
}

void Controller::GameStateManager::update_sounds(const Shared<Model::GameState>& new_game_state) {
    game_state->sound_effects.remove_if(
            [](Shared<View::TrackingSoundEffect>& sf) { return sf->has_ended(); });
    game_state->sound_effects.splice(game_state->sound_effects.end(),
                                     new_game_state->sound_effects);
}

void Controller::GameStateManager::update_animations(
        const Shared<Model::GameState>& new_game_state) {
    game_state->fires.remove_if(
            [](Shared<View::MuzzleFireAnimation>& a) { return a->has_ended(); });
    game_state->fires.splice(game_state->fires.end(), new_game_state->fires);
}

void Controller::GameStateManager::update_camera(const Shared<View::RenderedPlayer>& ref_player) {
    if (!ref_player)
        return;
    auto new_ref_player = ref_player;
    if (!new_ref_player->get_health())
        new_ref_player = game_state->get_any_player_alive_by_team(ref_player->get_team());
    if (!new_ref_player)
        return;
    auto reference_player_position = new_ref_player->get_position();
    game_state->camera.set_center(reference_player_position.get_x(),
                                  reference_player_position.get_y());
}

void Controller::GameStateManager::update_bomb_position(const DTO::GameStateDTO& dto) {
    load_bomb_explosion(dto);

    if (dto.round.bomb_planted && !game_state->bomb_position.has_value()) {
        auto pos = dto.round.bomb_position;
        game_state->bomb_position = SDL2pp::Point(pos.get_x(), pos.get_y());
    }
    if (dto.round.bomb_defused || dto.round.state != RoundState::Active) {
        game_state->bomb_position = std::nullopt;
    }
}

void Controller::GameStateManager::update_progress_bar(
        const Shared<View::RenderedPlayer>& ref_player) {
    if (!ref_player)
        return;
    if (ref_player->get_team() == Model::TeamID::CT) {
        if (!game_state->progress_bar && ref_player->is_defusing()) {
            game_state->progress_bar = make_shared<View::ProgressBarAnimation>(controller);
        } else if (!ref_player->is_defusing()) {
            game_state->progress_bar = nullptr;
        }
    } else if (ref_player->get_team() == Model::TeamID::TT) {
        if (!game_state->progress_bar && ref_player->get_planting_progress() > 0) {
            game_state->progress_bar = make_shared<View::ProgressBarAnimation>(controller);
        } else if (ref_player->get_planting_progress() == 0) {
            game_state->progress_bar = nullptr;
        }
    }
}

void Controller::GameStateManager::update_winner_message(const DTO::GameStateDTO& dto) {
    game_state->round_winner = dto.round.winner;
    if (game_state->winner_message && game_state->winner_message->has_ended())
        game_state->winner_message = nullptr;

    if (!game_state->winner_message && dto.round.state == RoundState::PostRound &&
        game_state->round_state == RoundState::Active) {
        game_state->winner_message =
                make_shared<View::WinnerTeamMessageAnimation>(controller, game_state->round_winner);
    }
}

void Controller::GameStateManager::update_stats(const DTO::GameStateDTO& dto) {
    game_state->time_left = dto.round.time_left;
    game_state->defusing_progress = dto.round.defusing_progress;
    game_state->first_team_victories = dto.ct_rounds_won;
    game_state->second_team_victories = dto.tt_rounds_won;
    game_state->game_winner = dto.winner;
    game_state->round_state = dto.round.state;
    game_state->bomb_defused = dto.round.bomb_defused;
    game_state->bomb_planted = dto.round.bomb_planted;
}

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

void Controller::GameStateManager::update(const DTO::GameStateDTO& game_state_dto) {
    auto new_game_state = make_shared<Model::GameState>();

    for (const auto& dto: game_state_dto.players) {
        auto player = make_shared<View::RenderedPlayer>(controller, std::move(dto.to_player()));
        new_game_state->players.insert({player->get_id(), player});
        load_shot_sound(new_game_state, player);
        load_reload_sound(new_game_state, player);
        load_animation(new_game_state, player);
    }

    std::lock_guard<std::mutex> lock(mutex);
    load_hit_sound(new_game_state);
    game_state->players = new_game_state->players;
    update_animations(new_game_state);
    update_sounds(new_game_state);
    load_bomb_state_sound(game_state_dto);

    auto ref_player = game_state->get_reference_player();
    load_start_round_sound(game_state_dto, ref_player);
    update_camera(ref_player);
    update_progress_bar(ref_player);

    update_dropped_weapons(game_state_dto);
    update_bomb_position(game_state_dto);
    update_winner_message(game_state_dto);
    update_stats(game_state_dto);
}
