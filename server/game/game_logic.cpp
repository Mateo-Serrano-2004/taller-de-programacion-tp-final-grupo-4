#include "game_logic.h"

#include <algorithm>
#include <cstdint>
#include <random>
#include <utility>

#include "common/weapon_id.h"
#include "server/parser/yaml_parser.h"

void GameLogic::buy_weapon(FullPlayer& player, Model::WeaponID weapon_id, Round& round) const {
    if (!round.is_buying())
        return;
    if (!player.is_alive())
        return;

    Shared<FullWeapon> dropped = shop.process_weapon_purchase(player, weapon_id);
    if (dropped) {
        round.add_dropped_weapon(DroppedWeapon(dropped, player.get_position()));
    }
}

void GameLogic::buy_ammo(FullPlayer& player, Model::SlotID slot_id, const Round& round) const {
    if (!round.is_buying())
        return;
    if (!player.is_alive())
        return;
    if (!player.has_type_weapon(slot_id))
        return;

    shop.process_ammo_purchase(player, slot_id);
}

bool GameLogic::is_in_bomb_zone(Physics::Vector2D player_pos,
                                const Physics::Vector2D& bomb_pos) const {
    return player_pos.distance_to(bomb_pos + Physics::Vector2D(TILE_SIZE / 2, TILE_SIZE / 2)) <=
           DEFUSE_RADIUS;
}

bool GameLogic::is_near_bomb_site(const Physics::Vector2D& player_pos,
                                  const std::vector<Physics::Vector2D>& bomb_sites) const {

    return std::any_of(bomb_sites.begin(), bomb_sites.end(), [&player_pos](const auto& site_pos) {
        Physics::Vector2D center_site = site_pos + Physics::Vector2D(TILE_SIZE / 2, TILE_SIZE / 2);
        if (player_pos.distance_to(center_site) <= BOMB_ZONE_RADIUS) {
            return true;
        }
        return false;
    });
}

void GameLogic::start_using_weapon(FullPlayer& player, const Round& round,
                                   const std::vector<Physics::Vector2D>& bomb_sites) const {
    if (!round.is_active())
        return;
    if (!player.is_alive())
        return;

    if (player.has_bomb_equipped()) {
        if (!is_near_bomb_site(player.get_position(), bomb_sites))
            return;
    }
    player.start_using_weapon();
}

Physics::Vector2D GameLogic::find_nearest_free_tile_around(
        const Physics::Vector2D& pos, const Physics::Vector2D& size,
        const std::vector<std::vector<TileType>>& type_matrix) const {

    const int max_y = type_matrix.size();
    const int max_x = (max_y > 0) ? type_matrix[0].size() : 0;

    int x1 = static_cast<int>(pos.get_x()) / TILE_SIZE;
    int y1 = static_cast<int>(pos.get_y()) / TILE_SIZE;
    int x2 = static_cast<int>(pos.get_x() + size.get_x() - 1) / TILE_SIZE;
    int y2 = static_cast<int>(pos.get_y() + size.get_y() - 1) / TILE_SIZE;

    std::set<std::pair<int, int>> occupied_tiles;
    for (int y = y1; y <= y2; ++y) {
        for (int x = x1; x <= x2; ++x) {
            occupied_tiles.emplace(x, y);
        }
    }

    std::vector<std::pair<int, int>> directions = {{0, -1},  {1, 0},  {0, 1}, {-1, 0},
                                                   {-1, -1}, {1, -1}, {1, 1}, {-1, 1}};

    for (const auto& [ox, oy]: occupied_tiles) {
        for (const auto& [dx, dy]: directions) {
            int nx = ox + dx;
            int ny = oy + dy;

            if (nx < 0 || ny < 0 || nx >= max_x || ny >= max_y)
                continue;
            if (occupied_tiles.count({nx, ny}))
                continue;

            if (type_matrix[ny][nx] == TileType::NOT_COLLIDABLE) {
                return Physics::Vector2D(nx * TILE_SIZE, ny * TILE_SIZE);
            }
        }
    }

    return pos;
}

void GameLogic::drop_equipped_weapon(FullPlayer& player, Round& round,
                                     const std::vector<std::vector<TileType>>& type_matrix) const {
    if (!player.is_alive())
        return;

    Shared<FullWeapon> dropped = player.drop_equipped_weapon();
    if (dropped) {
        Physics::Vector2D safe_pos = find_nearest_free_tile_around(player.get_position(),
                                                                   player.get_size(), type_matrix);
        round.add_dropped_weapon(DroppedWeapon(dropped, safe_pos));
    }
}

void GameLogic::start_reloading_weapon(FullPlayer& player, const Round& round) const {
    if (!round.is_active())
        return;
    if (!player.is_alive())
        return;
    player.start_reloading_weapon();
}

void GameLogic::start_defusing_bomb(FullPlayer& player, const Round& round) const {
    if (!round.is_active())
        return;
    if (!player.is_alive())
        return;
    if (!round.bomb_is_planted())
        return;
    if (player.get_team() != Model::TeamID::CT)
        return;
    if (!is_in_bomb_zone(player.get_position(), round.get_bomb_position()))
        return;
    if (round.bomb_is_being_defused())
        return;

    player.start_defusing_bomb();
}

void GameLogic::stop_defusing_bomb(FullPlayer& player) const { player.stop_defusing_bomb(); }

void GameLogic::stop_using_weapon(FullPlayer& player) const { player.stop_using_weapon(); }

void GameLogic::process_reloading(std::map<uint8_t, FullPlayer>& players, const Round& round,
                                  uint16_t frames_to_process) const {
    if (!round.is_active())
        return;
    for (auto& [id, player]: players) {
        if (!player.is_alive())
            continue;
        player.reload(frames_to_process);
    }
}

void GameLogic::process_defusing(std::map<uint8_t, FullPlayer>& players, Round& round) {
    if (!round.is_active())
        return;

    if (round.bomb_is_being_defused()) {
        if (round.player_id_defusing_bomb() == -1) {
            return;
        }

        auto it = players.find(round.player_id_defusing_bomb());
        if (it == players.end()) {
            round.notify_bomb_is_not_longer_being_defused();
            return;
        } else {
            auto& player = it->second;

            if (!player.is_alive() ||
                !is_in_bomb_zone(player.get_position(), round.get_bomb_position()) ||
                !player.is_defusing()) {
                player.stop_defusing_bomb();
                round.notify_bomb_is_not_longer_being_defused();
                return;
            }
        }
    }

    if (!round.bomb_is_being_defused()) {
        for (auto& [id, player]: players) {
            if (!player.is_alive())
                continue;
            if (player.get_team() != Model::TeamID::CT)
                continue;
            if (!round.bomb_is_planted())
                continue;
            if (!is_in_bomb_zone(player.get_position(), round.get_bomb_position())) {
                player.stop_defusing_bomb();
                continue;
            }
            if (!player.is_defusing())
                continue;

            round.notify_bomb_is_being_defused(id);

            break;
        }
    }
}

void GameLogic::process_shooting(std::map<uint8_t, FullPlayer>& players, Round& round,
                                 uint16_t frames_to_process,
                                 const std::vector<Physics::Vector2D>& bomb_sites,
                                 const MapMatrix& map_matrix) const {
    for (auto& [id, player]: players) {
        if (!player.is_alive())
            continue;

        if (player.has_bomb_equipped()) {
            if (!is_near_bomb_site(player.get_position(), bomb_sites)) {
                player.stop_using_weapon();
                continue;
            }
        }

        auto shot_info = player.shoot(frames_to_process);

        if (!shot_info.has_value())
            continue;

        if (shot_info->weapon_id == Model::WeaponID::BOMB) {
            if (!round.bomb_is_planted()) {
                round.notify_bomb_planted(player.get_position());
                player.remove_bomb();
            }
            continue;
        }

        std::vector<Impact> impacts =
                ShotManager::calculate_shot_impacts(shot_info.value(), players, map_matrix);
        if (!impacts.empty()) {
            apply_impacts(impacts, round, players);
        }
    }
}

void GameLogic::process_bomb_explosion(std::map<uint8_t, FullPlayer>& players, Round& round) const {
    if (!round.is_post_round() || !round.get_bomb_exploded())
        return;

    for (auto& [id, player]: players) {
        if (player.is_alive()) {
            player.take_damage(100);

            auto drops = player.drop_weapons();
            for (const auto& drop: drops) {
                round.add_dropped_weapon(drop);
            }
        }
    }
}

void GameLogic::apply_impacts(const std::vector<Impact>& impacts, Round& round,
                              std::map<uint8_t, FullPlayer>& players) const {
    for (const auto& impact: impacts) {
        if (!round.is_active())
            return;

        auto shooter = players.find(impact.shooter_id);
        if (shooter == players.end())
            continue;

        auto victim = players.find(impact.victim_id);
        if (victim == players.end())
            continue;

        if (victim->second.get_team() == shooter->second.get_team())
            continue;

        if (!victim->second.is_alive())
            continue;

        victim->second.take_damage(impact.damage);

        if (!victim->second.is_alive()) {

            round.notify_on_one_player_less(victim->second.get_team());
            shooter->second.add_money(YamlParser::getConfigData().game.killMoney);
            shooter->second.add_kill();

            auto drops = victim->second.drop_weapons();
            for (const auto& drop: drops) {
                round.add_dropped_weapon(drop);
            }
        }
    }
}

void GameLogic::assign_bomb_to_random_tt(std::map<uint8_t, FullPlayer>& players) {
    std::vector<FullPlayer*> tts;

    for (auto& [id, player]: players) {
        if (player.get_team() == Model::TeamID::TT && player.is_alive()) {
            tts.push_back(&player);
        }
    }

    if (!tts.empty()) {
        static std::default_random_engine generator(std::random_device{}());
        std::uniform_int_distribution<size_t> distribution(0, tts.size() - 1);
        size_t random_index = distribution(generator);

        auto bomb = WeaponFactory::create(Model::WeaponID::BOMB);
        tts[random_index]->give_bomb(bomb);
    }
}
