#include "game_logic.h"

#include <cstdint>
#include <random>

#include "common/weapon_id.h"

void GameLogic::buy_weapon(FullPlayer& player, Model::WeaponID weapon_id,
                           const Round& round) const {
    if (!round.is_buying())
        return;
    if (!player.is_alive())
        return;
    // TODO: Check player is in shop zone

    shop.process_weapon_purchase(player, weapon_id);
}

// dummy por ahora
bool GameLogic::is_in_bomb_zone(Physics::Vector2D player_position) const { return true; }

void GameLogic::start_using_weapon(FullPlayer& player, const Round& round) const {
    if (!round.is_active())
        return;
    if (!player.is_alive())
        return;

    if (player.has_bomb_equipped()) {
        if (!is_in_bomb_zone(player.get_position()))
            return;
    }
    player.start_using_weapon();
}

void GameLogic::start_reloading_weapon(FullPlayer& player, const Round& round) const {
    if (!round.is_active())
        return;
    if (!player.is_alive())
        return;
    player.start_reloading_weapon();
}

void GameLogic::stop_reloading_weapon(FullPlayer& player) const { player.stop_reloading_weapon(); }

void GameLogic::start_defusing_bomb(FullPlayer& player, const Round& round) const {
    if (!round.is_active())
        return;
    if (!player.is_alive())
        return;
    if (!round.bomb_is_planted())
        return;  // tiene sentido
    if (player.get_team() != Model::TeamID::CT)
        return;
    if (!is_in_bomb_zone(player.get_position()))
        return;
    if (round.bomb_is_being_defused())
        return;

    player.start_defusing_bomb();
}

void GameLogic::stop_defusing_bomb(FullPlayer& player) const { player.stop_defusing_bomb(); }

void GameLogic::stop_using_weapon(FullPlayer& player) const { player.stop_using_weapon(); }

void GameLogic::process_reloading(std::map<uint8_t, FullPlayer>& players, Round& round,
                                  uint16_t frames_to_process) const {
    if (!round.is_active())
        return;
    for (auto& [id, player]: players) {
        if (!player.is_alive()) {
            player.stop_reloading_weapon();  // el player cuando muere debe hacer esto
            continue;
        }
        player.reload(frames_to_process);
    }
}

void GameLogic::process_defusing(std::map<uint8_t, FullPlayer>& players, Round& round) {
    if (!round.is_active())
        return;

    if (round.bomb_is_being_defused()) {
        if (round.player_id_defusing_bomb() == -1) {
            return;
        }  // Solo chequeo seguridad, si esta siendo defuseada te da el int

        auto it = players.find(round.player_id_defusing_bomb());  // parseo int a uint
        if (it == players.end()) {
            round.notify_bomb_is_not_longer_being_defused();
            return;
        } else {
            auto& player = it->second;

            if (!player.is_alive() || !is_in_bomb_zone(player.get_position()) ||
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
            if (!is_in_bomb_zone(player.get_position())) {
                player.stop_defusing_bomb();
                continue;
            }  // ojo que deberia dejar de defusear si no esta plantada?
            if (!player.is_defusing())
                continue;

            round.notify_bomb_is_being_defused(id);

            break;
        }
    }
}

void GameLogic::process_shooting(std::map<uint8_t, FullPlayer>& players, Round& round,
                                 uint16_t frames_to_process) const {
    for (auto& [id, player]: players) {
        if (!player.is_alive())
            continue;

        // la idea es vovler a chequear que tiene que seguir en la zona de plantado.
        if (player.has_bomb_equipped()) {
            if (!is_in_bomb_zone(player.get_position())) {
                player.stop_using_weapon();  // si se fue para que reinicie
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
                ShotManager::calculate_shot_impacts(shot_info.value(), players);
        if (!impacts.empty()) {
            apply_impacts(impacts, round, players);
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
            shooter->second.add_money(800);
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
