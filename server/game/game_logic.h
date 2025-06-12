#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include <cstdint>
#include <map>
#include "common/weapon_id.h"

#include "model/full_player.h"

#include "round.h"
#include "shop.h"
#include "weapon_factory.h"
#include "server/game/model/impact.h"
#include "shot_manager.h"


class GameLogic {
private:
    Shop shop;
    void apply_impacts(const std::vector<Impact>& impacts, Round& round, std::map<uint8_t, FullPlayer>& players) const;
public:
    GameLogic() = default;

    void buy_weapon(FullPlayer& player, Model::WeaponID weapon_id, const Round& round) const;
    void start_using_weapon(FullPlayer& player, const Round& round) const;
    void stop_using_weapon(FullPlayer& player) const;
    void process_shooting(std::map<uint8_t, FullPlayer>& players, Round& round, uint16_t frames_to_process) const;
    
    ~GameLogic() = default;
};

#endif // GAME_LOGIC_H
