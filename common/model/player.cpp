#include "player.h"

#include <string>
#include <utility>

Model::Player::Player(short_id_t id, const std::string& name):
        id(id), skin_id(0), skin_piece(0), angle(0), name(name), position(0, 0), alive(true) {}

Model::Player::Player(short_id_t id, short_id_t skin_id, short_id_t skin_piece, angle_t angle,
                      const std::string& name, const Physics::Vector2D& position):
        id(id),
        skin_id(skin_id),
        skin_piece(skin_piece),
        angle(angle),
        name(name),
        position(position),
        alive(true) {}

short_id_t Model::Player::get_id() const { return id; }

short_id_t Model::Player::get_skin_id() const { return skin_id; }

short_id_t Model::Player::get_skin_piece() const { return skin_piece; }

angle_t Model::Player::get_angle() const { return angle; }

std::string Model::Player::get_name() const { return name; }

Physics::Vector2D Model::Player::get_position() const { return position; }

void Model::Player::set_skin_id(short_id_t new_skin_id) { skin_id = new_skin_id; }

void Model::Player::set_skin_piece(short_id_t new_skin_piece) { skin_piece = new_skin_piece; }

void Model::Player::set_angle(angle_t new_angle) { angle = new_angle; }

void Model::Player::set_position(Physics::Vector2D new_position) {
    position = std::move(new_position);
}

bool Model::Player::is_alive() const { return alive; }

DTO::PlayerDTO Model::Player::to_dto() const {
    return DTO::PlayerDTO(id, skin_id, skin_piece, angle, position.get_x(), position.get_y(), name);
}
