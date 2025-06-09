#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "common/weapon_id.h"

#include "model/full_player.h"

#include "round.h"
#include "shop.h"
#include "weapon_factory.h"

class GameLogic {
private:
    Shop shop;

public:
    GameLogic() = default;

    void buy_weapon(FullPlayer& player, Model::WeaponID weapon_id, const Round& round) const;

    ~GameLogic() = default;
};

#endif // GAME_LOGIC_H
