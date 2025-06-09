#include "game_logic.h"

#include <cstdint>

#include "common/weapon_id.h"

void GameLogic::buy_weapon(FullPlayer& player, Model::WeaponID weapon_id, const Round& round) const {
    if (!round.is_buying_phase()) return;
    if (!player.is_alive()) return;
    // FALTA: Cuando este mapa ver si el jugador está en zona de compra

    shop.process_weapon_purchase(player, weapon_id);
}
