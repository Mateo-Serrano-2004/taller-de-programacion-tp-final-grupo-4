#ifndef EVENTS_H
#define EVENTS_H

#include <cstdint>
#include <string>
#include <variant>

#include "common/model/vector_2d.h"
#include "common/role_id.h"
#include "common/slot_id.h"
#include "common/weapon_id.h"

class MovementEvent {
private:
    Physics::Vector2D direction;

public:
    MovementEvent(int8_t x, int8_t y): direction(x, y) {}
    Physics::Vector2D get_direction() const { return direction; }
};

class StopMovementEvent {
private:
    bool is_horizontal;

public:
    explicit StopMovementEvent(bool is_horizontal): is_horizontal(is_horizontal) {}
    bool is_movement_horizontal() const { return is_horizontal; }
};

class RotationEvent {
private:
    int16_t angle_in_degrees;

public:
    explicit RotationEvent(int16_t angle_in_degrees): angle_in_degrees(angle_in_degrees) {}
    int16_t get_angle_in_degrees() const { return angle_in_degrees; }
};

class DropWeaponEvent {
public:
    DropWeaponEvent() {}
};

class UseWeaponEvent {
public:
    UseWeaponEvent() {}
};

class StopUsingWeaponEvent {
public:
    StopUsingWeaponEvent() {}
};

class DefuseBombEvent {
public:
    DefuseBombEvent() {}
};

class StopDefusingBombEvent {
public:
    StopDefusingBombEvent() {}
};

class SwitchWeaponEvent {
private:
    Model::SlotID slot_id;

public:
    explicit SwitchWeaponEvent(Model::SlotID slot_id): slot_id(slot_id) {}
    Model::SlotID get_slot_id() const { return slot_id; }
};

class ReloadWeaponEvent {
public:
    ReloadWeaponEvent() {}
};

class PickRoleEvent {
private:
    Model::RoleID role_id;

public:
    explicit PickRoleEvent(Model::RoleID role_id): role_id(role_id) {}
    Model::RoleID get_role_id() const { return role_id; }
};

class BuyEvent {
private:
    Model::WeaponID weapon_id;

public:
    explicit BuyEvent(Model::WeaponID weapon_id): weapon_id(weapon_id) {}
    Model::WeaponID get_weapon_id() const { return weapon_id; }
};

class BuyAmmoEvent {
private:
    Model::SlotID slot_id;

public:
    explicit BuyAmmoEvent(Model::SlotID slot_id): slot_id(slot_id) {}
    Model::SlotID get_slot_id() const { return slot_id; }
};

class UsernameEvent {
private:
    std::string username;

public:
    explicit UsernameEvent(const std::string& username): username(username) {}
    const std::string& get_username() const { return username; }
};

class CreateGameEvent {
private:
    std::string party_name;
    std::string map_name;

public:
    CreateGameEvent(const std::string& party_name, const std::string& map_name):
            party_name(party_name), map_name(map_name) {}
    const std::string& get_party_name() const { return party_name; }
    const std::string& get_map_name() const { return map_name; }
};

class JoinGameEvent {
private:
    uint8_t game_id;

public:
    explicit JoinGameEvent(uint8_t game_id): game_id(game_id) {}
    uint8_t get_game_id() const { return game_id; }
};

class ListGamesEvent {
public:
    ListGamesEvent() {}
};

class MapRequestEvent {
public:
    MapRequestEvent() {}
};

class LeaveGameEvent {
public:
    LeaveGameEvent() {}
};

class QuitEvent {
public:
    QuitEvent() {}
};

using GameEventVariant =
        std::variant<LeaveGameEvent, MovementEvent, StopMovementEvent, RotationEvent,
                     DropWeaponEvent, UseWeaponEvent, DefuseBombEvent, SwitchWeaponEvent,
                     ReloadWeaponEvent, BuyEvent, BuyAmmoEvent, QuitEvent, PickRoleEvent,
                     StopUsingWeaponEvent, StopDefusingBombEvent>;

using EventVariant = std::variant<GameEventVariant, UsernameEvent, CreateGameEvent, MapRequestEvent,
                                  JoinGameEvent, ListGamesEvent>;

#endif  // EVENTS_H
