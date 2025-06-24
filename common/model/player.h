#ifndef COMMON_MODEL_PLAYER_H
#define COMMON_MODEL_PLAYER_H

#include <cstdint>
#include <string>

#include "common/definitions.h"
#include "common/role_id.h"
#include "common/team.h"
#include "server/parser/yaml_parser.h"

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
    bool defusing_bomb;
    bool reloading;
    short_id_t id;
    Model::RoleID role_id;
    angle_t angle;
    uint16_t money;
    std::string name;
    Physics::Vector2D position;
    Shared<Weapon> current_weapon;
    uint8_t health;
    Model::TeamID team;
    uint8_t deaths;
    uint8_t kills;
    uint8_t planting_progress;
    bool has_bomb;
    bool has_hit;

public:
    Player(short_id_t id, uint16_t money, const std::string& name, uint8_t health,
           Model::TeamID team, Model::RoleID role_id, Physics::Vector2D position);

    Player(bool shooting, bool defusing_bomb, bool reloading, short_id_t id, Model::RoleID role_id,
           angle_t angle, uint16_t money, const std::string& name,
           const Physics::Vector2D& position, Shared<Weapon> weapon, uint8_t health,
           Model::TeamID team, uint8_t deaths, uint8_t kills, uint8_t planting_progress,
           bool has_bomb, bool has_hit);

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(Player&&) = default;
    Player& operator=(Player&&) = default;

    bool is_alive() const;
    bool get_has_hit() const;
    bool is_shooting() const;
    bool is_defusing() const;
    bool is_reloading() const;
    bool get_has_bomb() const;
    short_id_t get_id() const;
    Model::RoleID get_role_id() const;
    angle_t get_angle() const;
    uint16_t get_money() const;
    std::string get_name() const;
    Physics::Vector2D get_position() const;
    Shared<Weapon> get_current_weapon() const;
    uint8_t get_health() const;
    Model::TeamID get_team() const;
    uint8_t get_kills() const;
    uint8_t get_deaths() const;
    uint8_t get_planting_progress() const;

    void set_alive(bool new_alive);
    void set_role_id(Model::RoleID new_sprite_id);
    void set_angle(angle_t new_angle);
    void set_money(uint16_t new_money);
    void set_position(Physics::Vector2D new_position);
    void set_current_weapon(Shared<Weapon> weapon);
    void set_new_team(Model::TeamID new_team);
    void add_kill();
    void add_death();
    void set_has_hit(bool new_has_hit);

    DTO::PlayerDTO to_dto() const;

    virtual ~Player() = default;
};
};  // namespace Model

#endif  // COMMON_MODEL_PLAYER_H
