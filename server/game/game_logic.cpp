#include "game_logic.h"

#include <cstdint>

#include "common/weapon_id.h"

void GameLogic::buy_weapon(FullPlayer& player, Model::WeaponID weapon_id, const Round& round) const {
    if (!round.is_buying_phase()) return;
    if (!player.is_alive()) return;
    // FALTA: Cuando este mapa ver si el jugador está en zona de compra

    shop.process_weapon_purchase(player, weapon_id);
}

void GameLogic::start_using_weapon(FullPlayer& player, const Round& round) const {
    if (!round.is_active_phase()) return;
    if (!player.is_alive()) return;
    player.start_using_weapon();
}

void GameLogic::stop_using_weapon(FullPlayer& player) const {
    player.stop_using_weapon();
}

void GameLogic::process_shooting(std::map<uint8_t, FullPlayer>& players, Round& round) const {
    if (!round.is_active_phase()) return; //podria llegar a cambiar??
    for (auto& [id, player] : players) {
        if (!player.is_alive()) continue;
        //if (!player.is_using_weapon()) continue; // aca el player no avisa esto, pero podes delegarlo al shoot
        player.shoot();
    }
}