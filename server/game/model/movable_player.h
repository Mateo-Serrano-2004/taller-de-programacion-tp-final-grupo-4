#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "common/definitions.h"
#include "common/model/player.h"
#include "common/model/vector_2d.h"

namespace Model {
class MovablePlayer: public Player {
private:
    Physics::Vector2D movement_direction;

public:
    MovablePlayer(short_id_t id, const std::string& name);

    MovablePlayer(short_id_t id, short_id_t skin_id, short_id_t skin_piece, angle_t angle,
                  std::string name, Physics::Vector2D position,
                  Physics::Vector2D movement_direction);

    MovablePlayer(MovablePlayer&&) = default;

    void update_movement_direction_by_merge(const Physics::Vector2D& direction);
    void stop_vertical_movement();
    void stop_horizontal_movement();
    void update_position();
    Physics::Vector2D get_direction() const;

    ~MovablePlayer() override = default;
};
};  // namespace Model

#endif  // PLAYER_H
