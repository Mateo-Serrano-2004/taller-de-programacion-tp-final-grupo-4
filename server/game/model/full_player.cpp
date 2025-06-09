#include "full_player.h"

#include <string>
#include <memory>
#include <cstdint>
#include <utility>

#include "common/definitions.h"
#include "common/weapon_id.h"
#include "common/slot_id.h"
#include "common/model/weapon.h"

#include "server/game/weapon_factory.h"

FullPlayer::FullPlayer(short_id_t id, const std::string& name)
: Model::Player(id, name),
  movement_direction(0, 0),
  secondary_weapon(WeaponFactory::create(Model::WeaponID::GLOCK)),
  knife(WeaponFactory::create(Model::WeaponID::KNIFE)) {
    current_weapon = secondary_weapon;
    money = 600;
}

void FullPlayer::update_movement_direction_by_merge(const Physics::Vector2D& direction) {
    coord_t new_x = direction.get_x();
    coord_t new_y = direction.get_y();
    if (new_x)
        this->movement_direction.set_x(new_x);
    if (new_y)
        this->movement_direction.set_y(new_y);
}

void FullPlayer::stop_vertical_movement() { movement_direction.set_y(0); }

void FullPlayer::stop_horizontal_movement() { movement_direction.set_x(0); }

Physics::Vector2D FullPlayer::get_direction() const { return movement_direction; }

void FullPlayer::update_position() {
    position += movement_direction;
    if (position.get_x() < 0)
        position.set_x(0);
    if (position.get_y() < 0)
        position.set_y(0);
}

void FullPlayer::equip_weapon_by_type(Model::SlotID type) {
    switch (type) {
        case Model::SlotID::KNIFE_SLOT:
            current_weapon = knife;
            break;
        case Model::SlotID::SECONDARY_WEAPON:
            if (secondary_weapon) current_weapon = secondary_weapon;
            break;
        case Model::SlotID::PRIMARY_WEAPON:
            if (primary_weapon) current_weapon = primary_weapon;
            break;
        case Model::SlotID::BOMB_SLOT:
            if (bomb) current_weapon = bomb;
            break;
    }
}

bool FullPlayer::can_pay(uint16_t price) { return money >= price; }

Shared<FullWeapon> FullPlayer::equip_new_weapon_and_drop_previous(Shared<FullWeapon> new_weapon) {
    if (!new_weapon) return nullptr;

    Model::SlotID type = std::static_pointer_cast<FullWeapon>(current_weapon)->get_slot_id();
    Shared<FullWeapon> dropped_weapon = nullptr;

    switch (type) {
        case Model::SlotID::SECONDARY_WEAPON:
            dropped_weapon = secondary_weapon;
            secondary_weapon = new_weapon;
            current_weapon = secondary_weapon;
            break;

        case Model::SlotID::PRIMARY_WEAPON:
            dropped_weapon = primary_weapon;
            primary_weapon = new_weapon;
            current_weapon = primary_weapon;
            break;
    }

    return dropped_weapon;
}

void FullPlayer::substract_money(uint16_t amount) {
    if (amount > money) money = 0;
    else money -= amount;
}
