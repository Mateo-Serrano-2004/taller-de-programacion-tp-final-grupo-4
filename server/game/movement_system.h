#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <cstdint>
#include <map>
#include <vector>

#include "common/definitions.h"
#include "model/full_player.h"
#include "server/parser/types.h"

#include "round.h"

class MovementSystem {
private:
    const MapMatrix& map_matrix;

    bool is_colliding_with_map(const Physics::Vector2D& position,
                               const Physics::Vector2D& size) const;

    bool is_colliding_with_other_players(const Physics::Vector2D& pos,
                                         const Physics::Vector2D& size, uint8_t current_id,
                                         const std::map<uint8_t, FullPlayer>& players) const;

    void try_pick_up_weapon(std::map<uint8_t, FullPlayer>& players, uint8_t player_id,
                            Round& round);

public:
    explicit MovementSystem(const MapMatrix& map_matrix);

    void process_movements(std::map<uint8_t, FullPlayer>& players, Round& round,
                           uint16_t frames_to_process, bool players_collisions_enabled);
};

#endif  // MOVEMENT_SYSTEM_H
