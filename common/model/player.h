#ifndef COMMON_MODEL_PLAYER_H
#define COMMON_MODEL_PLAYER_H

#include <cstdint>
#include <string>

#include "common/definitions.h"
#include "common/role_id.h"

#include "vector_2d.h"
#include "weapon.h"

namespace DTO {
class PlayerDTO;
};

namespace Model {
class Player {
protected:
    bool alive;
    bool shooting;
    short_id_t id;
    Model::RoleID role_id;
    angle_t angle;
    uint16_t money;
    std::string name;
    Physics::Vector2D position;
    Shared<Weapon> current_weapon;

public:
    Player(short_id_t id, const std::string& name);

    Player(
        bool shooting,
        short_id_t id,
        Model::RoleID role_id,
        angle_t angle,
        uint16_t money,
        const std::string& name,
        const Physics::Vector2D& position,
        Shared<Weapon> weapon
    );

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(Player&&) = default;
    Player& operator=(Player&&) = default;

    bool is_alive() const;
    bool is_shooting() const;
    short_id_t get_id() const;
    Model::RoleID get_role_id() const;
    angle_t get_angle() const;
    uint16_t get_money() const;
    std::string get_name() const;
    Physics::Vector2D get_position() const;
    Shared<Weapon> get_current_weapon() const;

    void set_alive(bool new_alive);
    void set_role_id(Model::RoleID new_sprite_id);
    void set_angle(angle_t new_angle);
    void set_money(uint16_t new_money);
    void set_position(Physics::Vector2D new_position);
    void set_current_weapon(Shared<Weapon> weapon);

    DTO::PlayerDTO to_dto() const;

    virtual ~Player() = default;
};
};  // namespace Model

#endif  // COMMON_MODEL_PLAYER_H
