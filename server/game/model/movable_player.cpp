#include "movable_player.h"

#include <string>

Model::MovablePlayer::MovablePlayer(short_id_t id, std::string name) : Model::Player(id, name) {}

Model::MovablePlayer::MovablePlayer(short_id_t id, short_id_t skin_id, short_id_t skin_piece, angle_t angle,
                                    std::string name, Physics::Vector2D position,
                                    Physics::Vector2D direction):
        Model::Player(id, skin_id, skin_piece, angle, name, position),
        movement_direction(std::move(direction)) {}

void Model::MovablePlayer::update_movement_direction_by_merge(const Physics::Vector2D& direction) {
    coord_t new_x = direction.get_x();
    coord_t new_y = direction.get_y();
    if (new_x) this->movement_direction.set_x(new_x);
    if (new_y) this->movement_direction.set_y(new_y);
}

void Model::MovablePlayer::stop_vertical_movement() {
    movement_direction.set_y(0);
}

void Model::MovablePlayer::stop_horizontal_movement() {
    movement_direction.set_x(0);
}

void Model::MovablePlayer::update_position() {
    position += movement_direction;
}
