#include "player.h"

#include <cmath>

Model::Player::Player(
    uint16_t id,
    int32_t x,
    int32_t y,
    int16_t angle,
    uint8_t skin_id
): default_angle(90),
   id(id),
   x(x),
   y(y),
   angle(angle),
   skin_id(skin_id),
   skin_piece(0) {}

uint16_t Model::Player::get_id() const {
    return id;
}

int32_t Model::Player::get_x() const {
    return x;
}

int32_t Model::Player::get_y() const {
    return y;
}

int16_t Model::Player::get_angle() const {
    return angle;
}

uint8_t Model::Player::get_skin_id() const {
    return skin_id;
}

uint8_t Model::Player::get_skin_piece() const {
    return skin_piece;
}

void Model::Player::set_x(int32_t new_x) {
    x = new_x;
}

void Model::Player::set_y(int32_t new_y) {
    y = new_y;
}

void Model::Player::set_angle(int16_t new_angle) {
    angle = default_angle + new_angle;
}

void Model::Player::set_skin_piece(uint8_t new_skin_piece) {
    skin_piece = new_skin_piece;
}
