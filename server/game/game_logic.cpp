#include "game_logic.h"

#include <cstdint>
#include "common/weapon_id.h"

void GameLogic::buy_weapon(FullPlayer& player, Model::WeaponID weapon_id, const Round& round) const {
    if (!round.is_buying()) return;
    if (!player.is_alive()) return;
    // TODO: Check player is in shop zone

    shop.process_weapon_purchase(player, weapon_id);
}

void GameLogic::start_using_weapon(FullPlayer& player, const Round& round) const {
    if (!round.is_active()) return;
    if (!player.is_alive()) return;
    player.start_using_weapon();
}

void GameLogic::stop_using_weapon(FullPlayer& player) const {
    player.stop_using_weapon();
}

void GameLogic::process_shooting(std::map<uint8_t, FullPlayer>& players, Round& round, uint16_t frames_to_process) const {
    for (auto& [id, player] : players) {
        if (!player.is_alive()) continue;

        auto shot_info = player.shoot(frames_to_process);
        if (!shot_info.has_value()) continue;
        std::vector<Impact> impacts = ShotManager::calculate_shot_impacts(shot_info.value(), players);
        if (!impacts.empty()) {
            apply_impacts(impacts, round, players);
        }
    }
}

void GameLogic::apply_impacts(const std::vector<Impact>& impacts, Round& round, std::map<uint8_t, FullPlayer>& players) const {
    for (const auto& impact : impacts) {
        if (!round.is_active()) return;

        auto shooter = players.find(impact.shooter_id);
        if (shooter == players.end()) continue;

        auto victim = players.find(impact.victim_id);
        if (victim == players.end()) continue;
        if (victim->second.get_team() == shooter->second.get_team()) continue;
        if (!victim->second.is_alive()) continue;

        victim->second.take_damage(impact.damage);

        if (!victim->second.is_alive()) {

            round.notify_on_one_player_less(victim->second.get_team());
            shooter->second.add_money(800);
        }
    }
}
