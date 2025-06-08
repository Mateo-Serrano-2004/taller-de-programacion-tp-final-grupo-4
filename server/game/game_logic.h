#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "common/weapon_type.h"
#include "round.h"
#include "model/movable_player.h"
#include "weapon_factory.h"
#include <iostream>
class GameLogic {
private:
    bool has_enough_money(const MovablePlayer& player, WeaponID weapon_id) const;
    uint16_t get_weapon_cost(WeaponID weapon_id) const;

public:
    GameLogic() = default;
    ~GameLogic() = default;

    void buy_weapon(MovablePlayer& player, WeaponID weapon_id, const Round& round) const;
};

#endif // GAME_LOGIC_H
