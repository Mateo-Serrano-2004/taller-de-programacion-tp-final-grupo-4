#ifndef EVENTS_H
#define EVENTS_H

#include <cstdint>
#include <string>
#include <variant>

#include "common/model/vector_2d.h"
#include "common/weapon_type.h" 

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
private:
    uint8_t weapon_id;

public:
    explicit DropWeaponEvent(uint8_t weapon_id): weapon_id(weapon_id) {}
    uint8_t get_weapon_id() const { return weapon_id; }
};

class UseWeaponEvent {
private:
    uint8_t weapon_id;

public:
    explicit UseWeaponEvent(uint8_t weapon_id): weapon_id(weapon_id) {}
    uint8_t get_weapon_id() const { return weapon_id; }
};

class DefuseBombEvent {
private:
    bool defusing;

public:
    explicit DefuseBombEvent(bool defusing): defusing(defusing) {}
    bool is_defusing() const { return defusing; }
};

class SwitchWeaponEvent {
private:
    WeaponType weapon_type;

public:
    explicit SwitchWeaponEvent(WeaponType weapon_type) : weapon_type(weapon_type) {}
    WeaponType get_weapon_type() const { return weapon_type; }
};

class ReloadWeaponEvent {
private:
    uint8_t weapon_id;

public:
    explicit ReloadWeaponEvent(uint8_t weapon_id): weapon_id(weapon_id) {}
    uint8_t get_weapon_id() const { return weapon_id; }
};

class SelectSideAndModelEvent {
private:
    uint8_t side;
    uint8_t model;

public:
    SelectSideAndModelEvent(uint8_t side, uint8_t model): side(side), model(model) {}
    uint8_t get_side() const { return side; }
    uint8_t get_model() const { return model; }
};

class BuyEvent {
private:
    uint8_t weapon_id;

public:
    explicit BuyEvent(uint8_t weapon_id): weapon_id(weapon_id) {}
    uint8_t get_weapon_id() const { return weapon_id; }
};

class BuyAmmoEvent {
private:
    uint8_t weapon_id;

public:
    explicit BuyAmmoEvent(uint8_t weapon_id): weapon_id(weapon_id) {}
    uint8_t get_weapon_id() const { return weapon_id; }
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
                     ReloadWeaponEvent, BuyEvent, BuyAmmoEvent, QuitEvent>;

using EventVariant = std::variant<GameEventVariant, UsernameEvent, CreateGameEvent, MapRequestEvent,
                                  JoinGameEvent, ListGamesEvent>;

#endif  // EVENTS_H
