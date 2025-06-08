#include "game_logic.h"
#include <cstdint>

void GameLogic::buy_weapon(Model::MovablePlayer& player, WeaponID weapon_id, const Round& round) const {
    if (!round.is_buying_phase()) return;
    if (!WeaponFactory::is_buyable(weapon_id)) return;
    if (!player.is_alive()) return;
    if (!has_enough_money(player, weapon_id)) return;
    // FALTA: Cuando este mapa ver si el jugador está en zona de compra

    std::unique_ptr<Weapon> weapon = WeaponFactory::create(weapon_id);
    if(!weapon) return;
    
    std::unique_ptr<Weapon> dropped_weapon = player.receive_weapon(std::move(weapon));
    if (dropped_weapon) {
         // FALTA: manejar drop del arma anterior cargarla en algun lado
        std::cout << "ARMA DROPEADA ES DE ID: " << static_cast<int>(dropped_weapon->to_dto().id) << std::endl;
    }

    player.subtract_money(WeaponFactory::get_price(weapon_id));

   
}

bool GameLogic::has_enough_money(const Model::MovablePlayer& player, WeaponID weapon_id) const {
    return player.get_money() >= WeaponFactory::get_price(weapon_id);
}
