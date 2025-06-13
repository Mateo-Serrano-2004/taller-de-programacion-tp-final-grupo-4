#ifndef SERVER_GAME_MODEL_FULL_PLAYER_H
#define SERVER_GAME_MODEL_FULL_PLAYER_H

#include <string>
#include <optional>
#include "common/definitions.h"
#include "common/slot_id.h"
#include "common/model/player.h"
#include "common/model/vector_2d.h"
#include "shot_info.h"
#include "full_weapon.h"

class FullPlayer: public Model::Player {
private:
    Physics::Vector2D movement_direction;

    Shared<FullWeapon> primary_weapon;
    Shared<FullWeapon> secondary_weapon;
    Shared<FullWeapon> knife;
    Shared<FullWeapon> bomb;

public:
    FullPlayer(short_id_t id, const std::string& name, Model::TeamID team, Model::RoleID role);

    FullPlayer(FullPlayer&&) = default;
    FullPlayer& operator=(FullPlayer&&) = default;

    Physics::Vector2D get_direction() const;

    void update_movement_direction_by_merge(const Physics::Vector2D& direction);
    void stop_vertical_movement();
    void stop_horizontal_movement();
    void update_position();
    void start_using_weapon();
    void stop_using_weapon();
    std::optional<ShotInfo> shoot(uint16_t frames_to_process);
    void take_damage(uint8_t damage);
    //no maneja tope de dinero
    void add_money(uint16_t money_to_be_added);
    void equip_weapon_by_type(Model::SlotID type);

    bool can_pay(uint16_t price);
    void substract_money(uint16_t amount);
    Shared<FullWeapon> equip_new_weapon_and_drop_previous(Shared<FullWeapon> new_weapon);

    void reset_for_new_round();

    ~FullPlayer() override = default;
};

#endif  // SERVER_GAME_MODEL_FULL_PLAYER_H
