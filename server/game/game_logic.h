#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <cstdint>
#include <map>
#include <vector>

#include "common/weapon_id.h"
#include "model/full_player.h"
#include "server/game/model/impact.h"

#include "round.h"
#include "shop.h"
#include "shot_manager.h"
#include "weapon_factory.h"
#include "server/game/model/dropped_weapon.h"


class GameLogic {
private:
    Shop shop;
    void apply_impacts(const std::vector<Impact>& impacts, Round& round,
                       std::map<uint8_t, FullPlayer>& players) const;
    bool is_in_bomb_zone(Physics::Vector2D player_position) const;

public:
    GameLogic() = default;

    void buy_weapon(FullPlayer& player, Model::WeaponID weapon_id, Round& round) const;
    void start_using_weapon(FullPlayer& player, const Round& round) const;
    void stop_using_weapon(FullPlayer& player) const;
    void process_shooting(std::map<uint8_t, FullPlayer>& players, Round& round,
                          uint16_t frames_to_process) const;
    void assign_bomb_to_random_tt(std::map<uint8_t, FullPlayer>& players);
    void start_defusing_bomb(FullPlayer& player, const Round& round) const;
    void stop_defusing_bomb(FullPlayer& player) const;
    void start_reloading_weapon(FullPlayer& player, const Round& round) const;
    void stop_reloading_weapon(FullPlayer& player) const;
    void process_defusing(std::map<uint8_t, FullPlayer>& players, Round& round);
    void process_reloading(std::map<uint8_t, FullPlayer>& players, const Round& round,
                           uint16_t frames_to_process) const;

    ~GameLogic() = default;
};

#endif  // GAME_LOGIC_H
