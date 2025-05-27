#include "../include/player.h"

#include <iostream>

Player::Player(uint8_t id, const std::string& username, Team team, int money)
    : id(id), username(username), position({0, 0}), direction({0, 0}), angle(0),
      team(team), health(100), money(money), is_alive(true), has_bomb(false) {}

void Player::set_direction(const Vector2D& dir) {
    direction = dir;
}

void Player::update_position() {
    if (!is_alive) return;
    position += direction;
    // por ahora depues chequeo con cosas y mapa
    position.x = std::max(0, position.x);
    position.y = std::max(0, position.y);
}

void Player::take_damage(int damage) {
    if (!is_alive) return;

    health -= damage;
    if (health <= 0) {
        health = 0;
        is_alive = false;
    }
}

bool Player::alive() const {
    return is_alive;
}

PlayerDTO Player::to_dto() const {
    PlayerDTO dto;
    dto.player_id = id;
    dto.name = username;
    dto.skin_id = 0; // TODO: skin_id real 
    dto.current_weapon = WeaponDTO{};
    dto.has_bomb = has_bomb ? 1 : 0;
    dto.health = health;
    dto.money = money;
    dto.position_x = static_cast<uint16_t>(position.x);
    dto.position_y = static_cast<uint16_t>(position.y);
    dto.angle = angle;

    return dto;
}