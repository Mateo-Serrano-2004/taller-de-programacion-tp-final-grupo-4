#include "game.h"

#include <exception>
#include <functional>
#include <mutex>
#include <optional>

#include "common/definitions.h"
#include "common/model/vector_2d.h"
#include "common/overloaded.h"
#include "common/periodic_clock.h"
#include "server/exception/invalid_game_exception.h"
#include "server/exception/invalid_player_exception.h"
#include "server/parser/yaml_parser.h"

void Game::with_valid_player(short_id_t player_id, std::function<void(FullPlayer&)> action) {
    auto it = players.find(player_id);
    if (it == players.end())
        return;
    action(it->second);
}

bool Game::is_playing_state() { return state == GameState::Playing; }

void Game::handle_use_weapon(const uint8_t& player_id) {
    if (!is_playing_state())
        return;
    with_valid_player(player_id, [this](FullPlayer& player) {
        gamelogic.start_using_weapon(player, round, bomb_sites);
    });
}

void Game::handle_reload(const uint8_t& player_id) {
    if (!is_playing_state())
        return;
    with_valid_player(player_id, [this](FullPlayer& player) {
        gamelogic.start_reloading_weapon(player, round);
    });
}

void Game::handle_start_defusing_bomb(const uint8_t& player_id) {
    if (!is_playing_state())
        return;
    with_valid_player(player_id,
                      [this](FullPlayer& player) { gamelogic.start_defusing_bomb(player, round); });
}

void Game::handle_stop_defusing_bomb(const uint8_t& player_id) {
    with_valid_player(player_id,
                      [this](FullPlayer& player) { gamelogic.stop_defusing_bomb(player); });
}

void Game::handle_stop_using_weapon(const uint8_t& player_id) {
    with_valid_player(player_id,
                      [this](FullPlayer& player) { gamelogic.stop_using_weapon(player); });
}

void Game::handle_drop_weapon(const uint8_t& player_id) {
    with_valid_player(player_id, [this](FullPlayer& player) {
        gamelogic.drop_equipped_weapon(player, round, map_matrix);
    });
}

void Game::handle_switch_weapon(const uint8_t& player_id, const SwitchWeaponEvent& event) {
    with_valid_player(player_id, [&event](FullPlayer& player) {
        player.equip_weapon_by_type(event.get_slot_id());
    });
}

void Game::handle_buy_ammo(const uint8_t& player_id, const BuyAmmoEvent& event) {
    if (!is_playing_state())
        return;

    with_valid_player(player_id, [this, &event](FullPlayer& player) {
        gamelogic.buy_ammo(player, event.get_slot_id(), round);
    });
}

void Game::handle_buy_weapon(const uint8_t& player_id, const BuyEvent& event) {
    if (!is_playing_state())
        return;

    with_valid_player(player_id, [this, &event](FullPlayer& player) {
        gamelogic.buy_weapon(player, event.get_weapon_id(), round);
    });
}

void Game::handle_leave_game(const uint8_t& player_id) {
    with_valid_player(player_id, [&](FullPlayer& player) {
        round.notify_on_one_player_less(player.get_team());
        players.erase(player.get_id());
    });

    try {
        client_queues.erase(player_id);
    } catch (const std::exception&) {}

    if (players.empty())
        kill();
}

void Game::handle_movement(const uint8_t& player_id, const MovementEvent& event) {
    with_valid_player(player_id, [&event](FullPlayer& player) {
        player.update_movement_direction_by_merge(event.get_direction());
    });
}

void Game::handle_stop_movement(const uint8_t& player_id, const StopMovementEvent& event) {
    with_valid_player(player_id, [&event](FullPlayer& player) {
        if (event.is_movement_horizontal()) {
            player.stop_horizontal_movement();
        } else {
            player.stop_vertical_movement();
        }
    });
}

void Game::handle_rotation(const uint8_t& player_id, const RotationEvent& event) {
    with_valid_player(player_id, [&event](FullPlayer& player) {
        player.set_angle(event.get_angle_in_degrees());
    });
}

void Game::handle_pick_role(const uint8_t player_id, const PickRoleEvent& event) {
    with_valid_player(player_id,
                      [&event](FullPlayer& player) { player.set_role_id(event.get_role_id()); });
}

void Game::handle(uint8_t player_id, const GameEventVariant& event) {
    std::visit(
            overloaded{
                    [player_id, this](const MovementEvent& e) { handle_movement(player_id, e); },
                    [player_id, this](const StopMovementEvent& e) {
                        handle_stop_movement(player_id, e);
                    },
                    [player_id, this](const LeaveGameEvent&) { handle_leave_game(player_id); },
                    [player_id, this](const QuitEvent&) { handle_leave_game(player_id); },
                    [player_id, this](const RotationEvent& e) { handle_rotation(player_id, e); },
                    [player_id, this](const PickRoleEvent& e) { handle_pick_role(player_id, e); },
                    [player_id, this](const SwitchWeaponEvent& e) {
                        handle_switch_weapon(player_id, e);
                    },
                    [player_id, this](const BuyEvent& e) { handle_buy_weapon(player_id, e); },
                    [player_id, this](const DropWeaponEvent&) { handle_drop_weapon(player_id); },
                    [player_id, this](const UseWeaponEvent&) { handle_use_weapon(player_id); },
                    [player_id, this](const StopUsingWeaponEvent&) {
                        handle_stop_using_weapon(player_id);
                    },
                    [player_id, this](const DefuseBombEvent&) {
                        handle_start_defusing_bomb(player_id);
                    },
                    [player_id, this](const StopDefusingBombEvent&) {
                        handle_stop_defusing_bomb(player_id);
                    },
                    [player_id, this](const ReloadWeaponEvent&) { handle_reload(player_id); },
                    [player_id, this](const BuyAmmoEvent& e) { handle_buy_ammo(player_id, e); }},
            event);
}

void Game::clear_game_queue() {
    std::pair<uint8_t, GameEventVariant> event_info;
    while (game_queue.try_pop(event_info)) {}
}

Physics::Vector2D Game::get_position_for_new_player(Model::TeamID team) {
    if (team == Model::TeamID::CT) {
        return ct_spawn_positions[0];
    }
    return tt_spawn_positions[0];
}

void Game::swap_teams() {
    for (auto& [id, player]: players) {
        if (player.get_team() == Model::TeamID::CT) {
            player.set_new_team(Model::TeamID::TT);
        } else if (player.get_team() == Model::TeamID::TT) {
            player.set_new_team(Model::TeamID::CT);
        } else {
            continue;
        }

        Model::RoleID current = player.get_role_id();

        switch (current) {
            case Model::RoleID::CT1:
                player.set_role_id(Model::RoleID::T1);
                break;
            case Model::RoleID::CT2:
                player.set_role_id(Model::RoleID::T2);
                break;
            case Model::RoleID::CT3:
                player.set_role_id(Model::RoleID::T3);
                break;
            case Model::RoleID::CT4:
                player.set_role_id(Model::RoleID::T4);
                break;
            case Model::RoleID::T1:
                player.set_role_id(Model::RoleID::CT1);
                break;
            case Model::RoleID::T2:
                player.set_role_id(Model::RoleID::CT2);
                break;
            case Model::RoleID::T3:
                player.set_role_id(Model::RoleID::CT3);
                break;
            case Model::RoleID::T4:
                player.set_role_id(Model::RoleID::CT4);
                break;
            default:
                break;
        }
    }
    std::swap(ct_rounds_won, tt_rounds_won);
}

void Game::start_new_round() {
    state = GameState::Playing;

    if (rounds_played == rounds_per_side) {
        swap_teams();
    }

    int ct_count = 0;
    int tt_count = 0;

    for (auto& [id, player]: players) {
        handle_stop_using_weapon(id);

        Model::TeamID player_team = player.get_team();
        if (player_team == Model::TeamID::CT) {
            player.reset_for_new_round(ct_spawn_positions[ct_count]);
            ct_count++;
        } else {
            player.reset_for_new_round(tt_spawn_positions[tt_count]);
            tt_count++;
        }
    }

    gamelogic.assign_bomb_to_random_tt(players);

    round = Round(ct_count, tt_count, GAME_FPS);
    rounds_played++;
}

void Game::update_players_that_won() {
    Model::TeamID winner = round.get_winner_team();

    if (winner == Model::TeamID::NONE)
        return;

    if (winner == Model::TeamID::CT) {
        ct_rounds_won++;
    } else if (winner == Model::TeamID::TT) {
        tt_rounds_won++;
    }

    for (auto& [player_id, player]: players) {
        if (player.get_team() == winner) {
            player.add_money(round_won_money);
        } else {
            player.add_money(round_lost_money);
        }
    }
}

void Game::process_frames(uint16_t frames_to_process) {
    movement_system.process_movements(players, round, frames_to_process,
                                      state != GameState::WaitingStart);
    gamelogic.process_defusing(players, round);
    round.update(frames_to_process);
    gamelogic.process_reloading(players, round, frames_to_process);
    gamelogic.process_shooting(players, round, frames_to_process, bomb_sites, map_matrix);
    gamelogic.process_bomb_explosion(players, round);

    if (round.ended()) {
        clear_game_queue();
        update_players_that_won();

        if (rounds_played == max_rounds) {
            state = GameState::Finished;
            kill();
            return;
        }
        broadcast_game_state();
        start_new_round();
    }
}

void Game::broadcast_game_state() {
    std::vector<DTO::PlayerDTO> player_dtos;
    for (auto& [id, player]: players) {
        player_dtos.push_back(player.to_dto());
        player.set_has_hit(false);
    }

    DTO::RoundDTO round_dto = round.to_dto();

    Model::TeamID winner = Model::TeamID::NONE;
    bool ended = (state == GameState::Finished);
    if (ended) {
        if (ct_rounds_won > tt_rounds_won)
            winner = Model::TeamID::CT;
        else if (tt_rounds_won > ct_rounds_won)
            winner = Model::TeamID::TT;
    }

    DTO::GameStateDTO game_snapshot(state, player_dtos, ended, winner, round_dto, ct_rounds_won,
                                    tt_rounds_won);

    for (auto& [id, queue]: client_queues) {
        try {
            queue->push(game_snapshot);
        } catch (const ClosedQueue&) {
            try {
                client_queues.erase(id);
            } catch (const std::exception&) {}
        } catch (const std::exception&) {}
    }
}

void Game::update_game_with_events() {
    std::pair<uint8_t, GameEventVariant> event_info;
    while (game_queue.try_pop(event_info)) {
        uint8_t player_id = event_info.first;
        GameEventVariant event = event_info.second;
        handle(player_id, event);
    }
}

void Game::tick(uint16_t frames_to_process) {
    std::lock_guard<std::mutex> lock(mutex);
    if (frames_to_process > 1) {
        process_frames(frames_to_process - 1);
    }

    update_game_with_events();
    process_frames();
    broadcast_game_state();
}

void Game::close() {
    kill();
    game_queue.close();
    join();
}

void Game::load_map_features() {
    for (size_t y = 0; y < map_matrix.size(); ++y) {
        for (size_t x = 0; x < map_matrix[y].size(); ++x) {
            TileType tile = map_matrix[y][x];
            int px = static_cast<int>(x) * TILE_SIZE;
            int py = static_cast<int>(y) * TILE_SIZE;

            switch (tile) {
                case TileType::CT_SPAWN:
                    ct_spawn_positions.emplace_back(px, py);
                    break;
                case TileType::TT_SPAWN:
                    tt_spawn_positions.emplace_back(px, py);
                    break;
                case TileType::BOMB_SITE:
                    bomb_sites.emplace_back(px, py);
                    break;
                default:
                    break;
            }
        }
    }
}

Game::Game(const std::string& party_name, const std::string& map_name, const MapMatrix& map_matrix):
        round(Round::create_warmup_round(GAME_FPS)),
        party_name(party_name),
        map_name(map_name),
        map_matrix(map_matrix),
        movement_system(MovementSystem(this->map_matrix)) {
    load_map_features();

    const auto& config = YamlParser::getConfigData();
    this->max_rounds = static_cast<uint8_t>(config.game.rounds);
    this->rounds_per_side = static_cast<uint8_t>(config.game.roundsPerSide);
    this->round_won_money = config.game.roundWonMoney;
    this->round_lost_money = config.game.roundLostMoney;

    start();
}

uint8_t Game::get_number_of_players() {
    std::lock_guard<std::mutex> lock(mutex);
    return players.size();
}

std::string Game::get_party_name() { return party_name; }

std::string Game::get_map_name() { return map_name; }

GameQueue& Game::get_queue() { return game_queue; }

bool Game::is_valid() { return round.is_warmup() && is_not_finished; }

bool Game::is_dead() { return !is_not_finished; }

void Game::add_player(const std::string& username, ClientQueue& client_queue, short_id_t player_id,
                      Model::TeamID team_id, Model::RoleID role_id) {
    std::lock_guard<std::mutex> lock(mutex);

    if (state != GameState::WaitingStart || players.size() == max_players) {
        throw InvalidGameException("Game no longer accepts players");
    }

    players.emplace(player_id, FullPlayer(player_id, username, team_id, role_id,
                                          get_position_for_new_player(team_id)));

    try {
        client_queues[player_id] = &client_queue;
    } catch (const std::exception&) {}

    round.notify_player_joined(team_id);
}

void Game::kill() { is_not_finished = false; }

void Game::run() {
    PeriodicClock clock(GAME_FPS);

    while (is_not_finished) {
        try {
            uint16_t frames_to_process = clock.sleep_and_get_frames();
            this->tick(frames_to_process);
        } catch (const std::exception&) {}
    }
}

Game::~Game() { close(); }
