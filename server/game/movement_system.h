#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <cstdint>
#include <map>
#include <vector>

#include "model/full_player.h"
#include "server/parser/types.h"

struct BoundingBox {
    int x, y, w, h;
};

class MovementSystem {
private:
    std::vector<BoundingBox> collidable_boxes;

    bool is_colliding_with_map(const Physics::Vector2D& position,
                               const Physics::Vector2D& size) const;

    bool is_colliding_with_other_players(const Physics::Vector2D& pos,
                                         const Physics::Vector2D& size,
                                         uint8_t current_id,
                                         const std::map<uint8_t, FullPlayer>& players) const;

public:
    explicit MovementSystem(const std::vector<std::vector<TileType>>& type_matrix);

    void process_movements(std::map<uint8_t, FullPlayer>& players, uint16_t frames_to_process);
};

#endif  // MOVEMENT_SYSTEM_H
