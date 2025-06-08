#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "common/definitions.h"
#include "common/model/player.h"
#include "common/model/vector_2d.h"
#include "common/weapon_type.h"
#include "weapon.h"
#include "knife.h"
#include "glock.h"
#include "ak47.h"
#include <iostream>

class MovablePlayer: public Model::Player {
private:
    Physics::Vector2D movement_direction;
    std::unique_ptr<Weapon> knife;
    std::unique_ptr<Weapon> secondary;
    std::unique_ptr<Weapon> primary;
    std::unique_ptr<Weapon> bomb;

    Weapon* equipped_weapon = nullptr;

    uint16_t money;

public:
    MovablePlayer(short_id_t id, const std::string& name);

    MovablePlayer(short_id_t id, short_id_t skin_id, short_id_t skin_piece, angle_t angle,
                  std::string name, Physics::Vector2D position,
                  Physics::Vector2D movement_direction, uint16_t money);

    MovablePlayer(MovablePlayer&&) = default;

    void update_movement_direction_by_merge(const Physics::Vector2D& direction);
    void stop_vertical_movement();
    void stop_horizontal_movement();
    void update_position();
    Physics::Vector2D get_direction() const;

    void equip_weapon_by_type(WeaponType type);
    std::unique_ptr<Weapon> receive_weapon(std::unique_ptr<Weapon> weapon);
    uint16_t get_money() const;
    void subtract_money(uint16_t amount);

    DTO::PlayerDTO to_dto() const;

    ~MovablePlayer() override = default;
};

#endif  // PLAYER_H
