#ifndef EVENTS_H
#define EVENTS_H

#include <cstdint>
#include <string>
#include <variant>

class MovementEvent {
private:
    int8_t x;
    int8_t y;
    uint8_t speed;

public:
    MovementEvent(int8_t x, int8_t y, uint8_t speed): x(x), y(y), speed(speed) {}
    int8_t get_x() const { return x; }
    int8_t get_y() const { return y; }
    uint8_t get_speed() const { return speed; }
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
    uint8_t weapon_id;

public:
    explicit SwitchWeaponEvent(uint8_t weapon_id): weapon_id(weapon_id) {}
    uint8_t get_weapon_id() const { return weapon_id; }
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

using GameEventVariant = std::variant<LeaveGameEvent, MovementEvent, RotationEvent, DropWeaponEvent,
                                      UseWeaponEvent, DefuseBombEvent, SwitchWeaponEvent,
                                      ReloadWeaponEvent, BuyEvent, BuyAmmoEvent, QuitEvent>;

using EventVariant = std::variant<GameEventVariant, UsernameEvent, CreateGameEvent, MapRequestEvent,
                                  JoinGameEvent, ListGamesEvent>;

#endif  // EVENTS_H
