#include "player.h"

Model::Player::Player(uint16_t x, uint16_t y, uint16_t skin_id)
: x(x),
  y(y),
  skin_id(skin_id),
  skin_piece(0) {}

uint16_t Model::Player::get_x() const {
    return x;
}

uint16_t Model::Player::get_y() const {
    return y;
}

uint16_t Model::Player::get_skin_id() const {
    return skin_id;
}

uint8_t Model::Player::get_skin_piece() const {
    return skin_piece;
}

void Model::Player::set_x(uint16_t new_x) {
    x = new_x;
}

void Model::Player::set_y(uint16_t new_y) {
    y = new_y;
}

void Model::Player::set_skin_piece(uint8_t new_skin_piece) {
    skin_piece = new_skin_piece;
}
