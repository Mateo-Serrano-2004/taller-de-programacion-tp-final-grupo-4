#include "movable_player.h"

#include <string>
#include <utility>

Model::MovablePlayer::MovablePlayer(short_id_t id, const std::string& name):
        Model::Player(id, name) {}

void Model::MovablePlayer::update_movement_direction_by_merge(const Physics::Vector2D& direction) {
    coord_t new_x = direction.get_x();
    coord_t new_y = direction.get_y();
    if (new_x)
        this->movement_direction.set_x(new_x);
    if (new_y)
        this->movement_direction.set_y(new_y);
}

void Model::MovablePlayer::stop_vertical_movement() { movement_direction.set_y(0); }

void Model::MovablePlayer::stop_horizontal_movement() { movement_direction.set_x(0); }

Physics::Vector2D Model::MovablePlayer::get_direction() const { return movement_direction; }

void Model::MovablePlayer::update_position() {
    position += movement_direction;
    if (position.get_x() < 0)
        position.set_x(0);
    if (position.get_y() < 0)
        position.set_y(0);
}
