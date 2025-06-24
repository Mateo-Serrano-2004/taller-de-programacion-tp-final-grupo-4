#include "full_player.h"

#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "common/definitions.h"
#include "common/model/weapon.h"
#include "common/slot_id.h"
#include "common/weapon_id.h"
#include "server/game/weapon_factory.h"
#include "server/parser/yaml_parser.h"

#include "bomb.h"

FullPlayer::FullPlayer(short_id_t id, const std::string& name, Model::TeamID team,
                       Model::RoleID role, Physics::Vector2D position):
        Model::Player(id, YamlParser::getConfigData().player.initialMoney, name,
                      YamlParser::getConfigData().player.health, team, role, position),
        movement_direction(0, 0),
        size(28, 28),
        secondary_weapon(WeaponFactory::create(Model::WeaponID::GLOCK)),
        knife(WeaponFactory::create(Model::WeaponID::KNIFE)),
        was_reloading(false),
        trying_reload(false) {
    current_weapon = secondary_weapon;
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

Physics::Vector2D FullPlayer::get_size() const { return size; }

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
            if (secondary_weapon)
                current_weapon = secondary_weapon;
            break;
        case Model::SlotID::PRIMARY_WEAPON:
            if (primary_weapon)
                current_weapon = primary_weapon;
            break;
        case Model::SlotID::BOMB_SLOT:
            if (bomb)
                current_weapon = bomb;
            break;
    }
}

bool FullPlayer::can_pay(uint16_t price) { return money >= price; }

Shared<FullWeapon> FullPlayer::equip_new_weapon_and_drop_previous(Shared<FullWeapon> new_weapon) {
    if (!new_weapon)
        return nullptr;

    Model::SlotID type = new_weapon->get_slot_id();
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
        case Model::SlotID::BOMB_SLOT:
            bomb = new_weapon;
            current_weapon = bomb;
            if (bomb)
                has_bomb = true;
            else
                has_bomb = false;
            break;
        default:
            return nullptr;
    }
    if (dropped_weapon)
        dropped_weapon->release_trigger();
    shooting = false;
    return dropped_weapon;
}

void FullPlayer::substract_money(uint16_t amount) {
    if (amount > money)
        money = 0;
    else
        money -= amount;
}

void FullPlayer::start_reloading_weapon() {
    if (!current_weapon || !alive)
        return;
    trying_reload = true;
    std::static_pointer_cast<FullWeapon>(current_weapon)->start_reloading();
}

void FullPlayer::reload(uint16_t frames_to_process) {
    if (!current_weapon || !alive || !trying_reload) {
        trying_reload = false;
        reloading = false;
        was_reloading = false;
        return;
    }

    auto weapon = std::static_pointer_cast<FullWeapon>(current_weapon);
    bool result =
            weapon->reload(frames_to_process);  // true si recara, false error o dejo de recargar

    reloading = (!was_reloading && result);
    was_reloading = result;
    trying_reload = result;
}


void FullPlayer::start_using_weapon() {
    if (!current_weapon || !alive)
        return;
    std::static_pointer_cast<FullWeapon>(current_weapon)->press_trigger();
}

void FullPlayer::stop_using_weapon() {
    if (!current_weapon)
        return;
    std::static_pointer_cast<FullWeapon>(current_weapon)->release_trigger();
    shooting = false;
    planting_progress = 0;
}

void FullPlayer::start_defusing_bomb() {
    if (!alive || team != Model::TeamID::CT)
        return;
    defusing_bomb = true;
}

void FullPlayer::stop_defusing_bomb() { defusing_bomb = false; }

Physics::Vector2D FullPlayer::weapon_position() const {
    return Physics::Vector2D(position.get_x() + size.get_x() / 2,
                             position.get_y() + size.get_y() / 2);
}


std::optional<ShotInfo> FullPlayer::shoot(uint16_t frames_to_process) {
    if (!current_weapon || !alive) {
        shooting = false;
        return std::nullopt;
    }

    auto weapon = std::static_pointer_cast<FullWeapon>(current_weapon);
    auto shot_info = weapon->shoot(frames_to_process);

    if (weapon->get_weapon_id() == Model::WeaponID::BOMB)
        planting_progress = std::static_pointer_cast<Bomb>(current_weapon)->get_planting_progress();

    if (!shot_info.has_value()) {
        shooting = false;
        return std::nullopt;
    }

    shooting = true;
    return ShotInfo(id, weapon_position(), angle, weapon->get_weapon_id(), shot_info.value());
}

void FullPlayer::take_damage(uint8_t damage) {
    if (!is_alive())
        return;
    if (health <= damage) {
        health = 0;
        alive = false;
        add_death();
    } else {
        health -= damage;
    }
    has_hit = true;
}

void FullPlayer::add_money(uint16_t money_to_be_added) { money += money_to_be_added; }

void FullPlayer::reset_for_new_round(Physics::Vector2D new_position) {
    position = new_position;
    if (!alive) {
        secondary_weapon = WeaponFactory::create(Model::WeaponID::GLOCK);
        current_weapon = secondary_weapon;
    }
    alive = true;
    health = 100;
    defusing_bomb = false;
    reloading = false;
    planting_progress = 0;
    bomb.reset();
    has_bomb = false;
    has_hit = false;
}

bool FullPlayer::has_bomb_equipped() const {
    if (!current_weapon)
        return false;
    return current_weapon->get_weapon_id() == Model::WeaponID::BOMB;
}

Shared<FullWeapon> FullPlayer::remove_bomb() {
    if (!current_weapon)
        return nullptr;

    Shared<FullWeapon> dropped_bomb = nullptr;
    planting_progress = 0;

    if (current_weapon->get_weapon_id() == Model::WeaponID::BOMB) {

        dropped_bomb = bomb;
        bomb.reset();

        equip_weapon_by_type(Model::SlotID::KNIFE_SLOT);
    }

    has_bomb = false;
    return dropped_bomb;
}

std::vector<DroppedWeapon> FullPlayer::drop_weapons() {
    std::vector<DroppedWeapon> drops;
    const auto pos = get_position();

    if (primary_weapon) {
        drops.emplace_back(primary_weapon, pos);
        primary_weapon.reset();
    }

    if (secondary_weapon) {
        drops.emplace_back(secondary_weapon, pos);
        secondary_weapon.reset();
    }

    if (bomb) {
        drops.emplace_back(bomb, pos);
        bomb.reset();
    }

    has_bomb = false;
    planting_progress = 0;
    equip_weapon_by_type(Model::SlotID::KNIFE_SLOT);  // por las dudas

    return drops;
}

Shared<FullWeapon> FullPlayer::drop_equipped_weapon() {
    if (!current_weapon)
        return nullptr;

    Shared<FullWeapon> dropped_weapon = nullptr;
    auto full_weapon = std::dynamic_pointer_cast<FullWeapon>(current_weapon);

    switch (full_weapon->get_slot_id()) {
        case Model::SlotID::SECONDARY_WEAPON:
            dropped_weapon = secondary_weapon;
            secondary_weapon = nullptr;
            break;

        case Model::SlotID::PRIMARY_WEAPON:
            dropped_weapon = primary_weapon;
            primary_weapon = nullptr;
            break;

        case Model::SlotID::BOMB_SLOT:
            dropped_weapon = bomb;
            bomb = nullptr;
            has_bomb = false;
            break;

        case Model::SlotID::KNIFE_SLOT:
            return nullptr;
    }

    if (dropped_weapon)
        dropped_weapon->release_trigger();

    shooting = false;
    planting_progress = 0;
    equip_weapon_by_type(Model::SlotID::KNIFE_SLOT);
    return dropped_weapon;
}

bool FullPlayer::has_primary_weapon() const { return primary_weapon != nullptr; }

bool FullPlayer::has_secondary_weapon() const { return secondary_weapon != nullptr; }

bool FullPlayer::has_type_weapon(Model::SlotID slot_id) const {
    switch (slot_id) {
        case Model::SlotID::PRIMARY_WEAPON:
            return has_primary_weapon();
        case Model::SlotID::SECONDARY_WEAPON:
            return has_secondary_weapon();
        case Model::SlotID::BOMB_SLOT:
            return has_bomb;
        default:
            return false;
    }
}

void FullPlayer::add_ammo(Model::SlotID slot_id) {
    switch (slot_id) {
        case Model::SlotID::PRIMARY_WEAPON:
            primary_weapon->add_ammo();
            break;
        case Model::SlotID::SECONDARY_WEAPON:
            secondary_weapon->add_ammo();
            break;
        default:
            return;
    }
}

void FullPlayer::give_bomb(Shared<FullWeapon> new_bomb) {
    bomb = new_bomb;
    if (bomb)
        has_bomb = true;
}
