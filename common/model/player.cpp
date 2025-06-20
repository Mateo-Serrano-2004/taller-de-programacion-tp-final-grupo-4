#include "player.h"

#include <cstdint>
#include <string>
#include <utility>

#include "common/DTO/player_dto.h"
#include "common/DTO/weapon_dto.h"
#include "common/weapon_id.h"

Model::Player::Player(short_id_t id, const std::string& name, Model::TeamID team,
                      Model::RoleID role_id, Physics::Vector2D position):
        alive(true),
        shooting(false),
        defusing_bomb(false),
        reloading(false),
        id(id),
        role_id(role_id),
        angle(0),
        money(0),
        name(name),
        position(position),
        health(100),
        team(team) {}

Model::Player::Player(bool shooting, bool defusing_bomb, bool reloading, short_id_t id,
                      Model::RoleID role_id, angle_t angle, uint16_t money, const std::string& name,
                      const Physics::Vector2D& position, Shared<Model::Weapon> weapon,
                      uint8_t health, Model::TeamID team):
        alive(true),
        shooting(shooting),
        defusing_bomb(defusing_bomb),
        reloading(reloading),
        id(id),
        role_id(role_id),
        angle(angle),
        money(money),
        name(name),
        position(position),
        current_weapon(weapon),
        health(health),
        team(team) {}

bool Model::Player::is_alive() const { return alive; }

bool Model::Player::is_shooting() const { return shooting; }

bool Model::Player::is_defusing() const { return defusing_bomb; }

bool Model::Player::is_reloading() const { return reloading; }

short_id_t Model::Player::get_id() const { return id; }

Model::RoleID Model::Player::get_role_id() const { return role_id; }

angle_t Model::Player::get_angle() const { return angle; }

uint16_t Model::Player::get_money() const { return money; }

std::string Model::Player::get_name() const { return name; }

Physics::Vector2D Model::Player::get_position() const { return position; }

void Model::Player::set_alive(bool new_alive) { alive = new_alive; }

void Model::Player::set_role_id(Model::RoleID new_role_id) { role_id = new_role_id; }

void Model::Player::set_angle(angle_t new_angle) { angle = new_angle; }

void Model::Player::set_money(uint16_t new_money) { money = new_money; }

void Model::Player::set_position(Physics::Vector2D new_position) {
    position = std::move(new_position);
}

void Model::Player::set_current_weapon(Shared<Model::Weapon> weapon) { current_weapon = weapon; }

uint8_t Model::Player::get_health() const { return health; }

Model::TeamID Model::Player::get_team() const { return team; }

void Model::Player::set_new_team(Model::TeamID new_team) { team = new_team; }

Shared<Model::Weapon> Model::Player::get_current_weapon() const { return current_weapon; }

DTO::PlayerDTO Model::Player::to_dto() const {
    return DTO::PlayerDTO(id, (short_id_t)(role_id), angle, money, position.get_x(),
                          position.get_y(), name, current_weapon->to_dto(), shooting, defusing_bomb,
                          reloading, health, (short_id_t)(team));
}
