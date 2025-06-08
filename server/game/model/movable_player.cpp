#include "movable_player.h"

#include <string>
#include <utility>

Model::MovablePlayer::MovablePlayer(short_id_t id, const std::string& name)
    : Model::Player(id, name),
      movement_direction(0, 0),
      knife(std::make_unique<Knife>()),
      secondary(std::make_unique<Glock>()),
      primary(nullptr),
      bomb(nullptr),
      equipped_weapon(nullptr),
      money(800)
{
    equipped_weapon = knife.get();
}

Model::MovablePlayer::MovablePlayer(short_id_t id, short_id_t skin_id, short_id_t skin_piece,
                                    angle_t angle, std::string name, Physics::Vector2D position,
                                    Physics::Vector2D direction, uint16_t money)
    : Model::Player(id, skin_id, skin_piece, angle, name, position),
      movement_direction(std::move(direction)),
      knife(std::make_unique<Knife>()),
      secondary(std::make_unique<Glock>()),
      primary(nullptr),
      bomb(nullptr),
      equipped_weapon(nullptr),
      money(money)
{
    equipped_weapon = knife.get();
}

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

void Model::MovablePlayer::equip_weapon_by_type(WeaponType type) {
    switch (type) {
        case WeaponType::KNIFE:
            if (knife) equipped_weapon = knife.get();
            break;
        case WeaponType::SECONDARY:
            if (secondary) equipped_weapon = secondary.get();
            break;
        case WeaponType::PRIMARY:
            if (primary) equipped_weapon = primary.get();
            break;
        case WeaponType::BOMB:
            if (bomb) equipped_weapon = bomb.get();
            break;
    }
}

void Model::MovablePlayer::subtract_money(uint16_t amount) {
    if (amount > money) money = 0;
    else money -= amount;
}

uint16_t Model::MovablePlayer::get_money() const {
    return money;
}

void Model::MovablePlayer::receive_weapon(std::unique_ptr<Weapon> weapon) {
    if (!weapon) return;

    WeaponType type = weapon->get_weapon_type();
    // FALTA: Que acá retorne el ownership del arma vieja para el drop luego (según caso)
    switch (type) {
        case WeaponType::KNIFE:
            knife = std::move(weapon);
            equipped_weapon = knife.get();
            break;
        case WeaponType::SECONDARY:
            secondary = std::move(weapon);
            equipped_weapon = secondary.get();
            break;
        case WeaponType::PRIMARY:
            primary = std::move(weapon);
            equipped_weapon = primary.get();
            break;
        case WeaponType::BOMB:
            bomb = std::move(weapon);
            equipped_weapon = bomb.get();
            break;
    }
}


DTO::PlayerDTO Model::MovablePlayer::to_dto() const {
    DTO::PlayerDTO dto = Player::to_dto();
    dto.weapon = equipped_weapon ? equipped_weapon->to_dto() : WeaponDTO();
    return dto;
}