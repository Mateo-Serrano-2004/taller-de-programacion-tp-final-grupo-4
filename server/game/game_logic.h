#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <cstdint>
#include <map>
#include <set>
#include <vector>

#include "common/definitions.h"
#include "common/weapon_id.h"
#include "model/full_player.h"
#include "server/game/model/dropped_weapon.h"
#include "server/game/model/impact.h"
#include "server/parser/types.h"

#include "round.h"
#include "shop.h"
#include "shot_manager.h"
#include "weapon_factory.h"

class GameLogic {
private:
    Shop shop;
    void apply_impacts(const std::vector<Impact>& impacts, Round& round,
                       std::map<uint8_t, FullPlayer>& players) const;
    bool is_in_bomb_zone(Physics::Vector2D player_pos, const Physics::Vector2D& bomb_pos) const;
    bool is_near_bomb_site(const Physics::Vector2D& player_pos,
                           const std::vector<Physics::Vector2D>& bomb_sites) const;
    Physics::Vector2D find_nearest_free_tile_around(
            const Physics::Vector2D& pos, const Physics::Vector2D& size,
            const std::vector<std::vector<TileType>>& type_matrix) const;

public:
    GameLogic() = default;

    void buy_weapon(FullPlayer& player, Model::WeaponID weapon_id, Round& round) const;
    void buy_ammo(FullPlayer& player, Model::SlotID slot_id, const Round& round) const;
    void start_using_weapon(FullPlayer& player, const Round& round,
                            const std::vector<Physics::Vector2D>& bomb_sites) const;
    void stop_using_weapon(FullPlayer& player) const;
    void drop_equipped_weapon(FullPlayer& player, Round& round,
                              const std::vector<std::vector<TileType>>& type_matrix) const;
    void process_shooting(std::map<uint8_t, FullPlayer>& players, Round& round,
                          uint16_t frames_to_process,
                          const std::vector<Physics::Vector2D>& bomb_sites,
                          const MapMatrix& map_matrix) const;
    void process_bomb_explosion(std::map<uint8_t, FullPlayer>& players, Round& round) const;
    void assign_bomb_to_random_tt(std::map<uint8_t, FullPlayer>& players);
    void start_defusing_bomb(FullPlayer& player, const Round& round) const;
    void stop_defusing_bomb(FullPlayer& player) const;
    void start_reloading_weapon(FullPlayer& player, const Round& round) const;
    void process_defusing(std::map<uint8_t, FullPlayer>& players, Round& round);
    void process_reloading(std::map<uint8_t, FullPlayer>& players, const Round& round,
                           uint16_t frames_to_process) const;

    ~GameLogic() = default;
};

#endif  // GAME_LOGIC_H
