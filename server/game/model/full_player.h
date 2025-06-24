#ifndef SERVER_GAME_MODEL_FULL_PLAYER_H
#define SERVER_GAME_MODEL_FULL_PLAYER_H

#include <optional>
#include <string>
#include <vector>

#include "common/definitions.h"
#include "common/model/player.h"
#include "common/model/vector_2d.h"
#include "common/slot_id.h"

#include "dropped_weapon.h"
#include "full_weapon.h"
#include "shot_info.h"

class FullPlayer: public Model::Player {
private:
    Physics::Vector2D movement_direction;
    Physics::Vector2D size;

    Shared<FullWeapon> primary_weapon;
    Shared<FullWeapon> secondary_weapon;
    Shared<FullWeapon> knife;
    Shared<FullWeapon> bomb;
    Physics::Vector2D weapon_position() const;
    bool was_reloading;
    bool trying_reload;

public:
    FullPlayer(short_id_t id, const std::string& name, Model::TeamID team, Model::RoleID role,
               Physics::Vector2D position);

    FullPlayer(FullPlayer&&) = default;
    FullPlayer& operator=(FullPlayer&&) = default;

    Physics::Vector2D get_direction() const;
    Physics::Vector2D get_size() const;

    void update_movement_direction_by_merge(const Physics::Vector2D& direction);
    void stop_vertical_movement();
    void stop_horizontal_movement();
    void update_position();
    void start_using_weapon();
    void stop_using_weapon();
    void start_reloading_weapon();
    void reload(uint16_t frames_to_process);
    std::optional<ShotInfo> shoot(uint16_t frames_to_process);
    void take_damage(uint8_t damage);

    void add_money(uint16_t money_to_be_added);
    void equip_weapon_by_type(Model::SlotID type);
    Shared<FullWeapon> drop_equipped_weapon();
    void add_ammo(Model::SlotID slot_id);

    bool can_pay(uint16_t price);
    bool has_bomb_equipped() const;
    void substract_money(uint16_t amount);
    bool has_primary_weapon() const;
    bool has_secondary_weapon() const;
    bool has_type_weapon(Model::SlotID slot_id) const;
    Shared<FullWeapon> equip_new_weapon_and_drop_previous(Shared<FullWeapon> new_weapon);

    void reset_for_new_round(Physics::Vector2D new_position);

    Shared<FullWeapon> remove_bomb();

    void give_bomb(Shared<FullWeapon> new_bomb);

    std::vector<DroppedWeapon> drop_weapons();

    void start_defusing_bomb();
    void stop_defusing_bomb();

    ~FullPlayer() override = default;
};

#endif  // SERVER_GAME_MODEL_FULL_PLAYER_H
