#include "movable_player.h"

#include <string>
#include <utility>

#include "common/model/weapon.h"

MovablePlayer::MovablePlayer(short_id_t id, const std::string& name)
    : Model::Player(id, name),
      movement_direction(0, 0),
      knife(std::make_unique<Knife>()),
      secondary(std::make_unique<Glock>()),
      primary(nullptr),
      bomb(nullptr),
      equipped_weapon(nullptr),
      money(800)
{
    equipped_weapon = secondary.get();
}

MovablePlayer::MovablePlayer(short_id_t id, short_id_t skin_id, short_id_t skin_piece,
                                    angle_t angle, std::string name, Physics::Vector2D position,
                                    Physics::Vector2D direction, uint16_t money)
    : Model::Player(id, skin_id, skin_piece, angle, name, position, Model::Weapon()),
      movement_direction(std::move(direction)),
      knife(std::make_unique<Knife>()),
      secondary(std::make_unique<Glock>()),
      primary(nullptr),
      bomb(nullptr),
      equipped_weapon(nullptr),
      money(money)
{
    equipped_weapon = secondary.get();
}

void MovablePlayer::update_movement_direction_by_merge(const Physics::Vector2D& direction) {
    coord_t new_x = direction.get_x();
    coord_t new_y = direction.get_y();
    if (new_x)
        this->movement_direction.set_x(new_x);
    if (new_y)
        this->movement_direction.set_y(new_y);
}

void MovablePlayer::stop_vertical_movement() { movement_direction.set_y(0); }

void MovablePlayer::stop_horizontal_movement() { movement_direction.set_x(0); }

Physics::Vector2D MovablePlayer::get_direction() const { return movement_direction; }

void MovablePlayer::update_position() {
    position += movement_direction;
    if (position.get_x() < 0)
        position.set_x(0);
    if (position.get_y() < 0)
        position.set_y(0);
}

void MovablePlayer::equip_weapon_by_type(WeaponType type) {
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

void MovablePlayer::subtract_money(uint16_t amount) {
    if (amount > money) money = 0;
    else money -= amount;
}

uint16_t MovablePlayer::get_money() const {
    return money;
}

std::unique_ptr<Weapon> MovablePlayer::receive_weapon(std::unique_ptr<Weapon> weapon) {
    if (!weapon) return nullptr;

    WeaponType type = weapon->get_weapon_type();
    std::unique_ptr<Weapon> dropped_weapon = nullptr;

    switch (type) {
        case WeaponType::KNIFE:
            dropped_weapon = std::move(knife);
            knife = std::move(weapon);
            equipped_weapon = knife.get();
            break;

        case WeaponType::SECONDARY:
            dropped_weapon = std::move(secondary);
            secondary = std::move(weapon);
            equipped_weapon = secondary.get();
            break;

        case WeaponType::PRIMARY:
            dropped_weapon = std::move(primary);
            primary = std::move(weapon);
            equipped_weapon = primary.get();
            break;

        case WeaponType::BOMB:
            dropped_weapon = std::move(bomb);
            bomb = std::move(weapon);
            equipped_weapon = bomb.get();
            break;
    }

    return dropped_weapon;
}


DTO::PlayerDTO MovablePlayer::to_dto() const {
    DTO::PlayerDTO dto = Player::to_dto();
    dto.weapon_dto = equipped_weapon ? equipped_weapon->to_dto() : DTO::WeaponDTO();
    return dto;
}
