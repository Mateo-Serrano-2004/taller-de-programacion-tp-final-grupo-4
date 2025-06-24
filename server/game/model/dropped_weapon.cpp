#include "dropped_weapon.h"

#include <utility>

DroppedWeapon::DroppedWeapon(Shared<FullWeapon> weapon, const Physics::Vector2D& position):
        position(position), weapon(std::move(weapon)) {}

const Physics::Vector2D& DroppedWeapon::get_position() const { return position; }

const Shared<FullWeapon>& DroppedWeapon::get_weapon() const { return weapon; }

DTO::DropWeaponDTO DroppedWeapon::to_dto() const {
    return DTO::DropWeaponDTO(weapon->get_weapon_id(), static_cast<uint16_t>(position.get_x()),
                              static_cast<uint16_t>(position.get_y()));
}
