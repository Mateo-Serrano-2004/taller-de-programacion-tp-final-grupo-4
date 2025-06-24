#ifndef ROUND_H
#define ROUND_H

#include <cstdint>
#include <vector>

#include "common/DTO/round_dto.h"
#include "common/model/vector_2d.h"
#include "server/game/model/dropped_weapon.h"
#include "server/parser/yaml_parser.h"

class Round {
private:
    Model::TeamID winner_team = Model::TeamID::NONE;

    RoundState state;
    int number_of_ct_alive;
    int number_of_tt_alive;

    bool bomb_planted;
    bool bomb_defused;
    Physics::Vector2D bomb_position;

    int ticks_for_warmup_phase;
    int ticks_for_buying_phase;
    int ticks_for_playing_phase;
    int ticks_for_post_round_phase;
    int bomb_total_ticks;

    int active_ticks_remaining;
    int defusing_ticks;
    int defusing_ticks_remaining;

    bool bomb_being_defused;
    int player_defusing_bomb;
    bool is_warmup_round;
    bool bomb_exploded;

    int fps;

    void update_if_finished_warmup();
    void update_if_finished_buying();
    void update_if_finished_playing();
    void update_if_finished_post_round();
    int get_ticks_remaining() const;
    void check_if_finished_defusing(int frames_to_process);

    std::vector<DroppedWeapon> dropped_weapons;

public:
    Round(int ct_alive, int tt_alive, int fps);

    static Round create_warmup_round(int fps);

    Model::TeamID get_winner_team() const;
    RoundState get_state() const;
    bool is_warmup() const;
    bool is_buying() const;
    bool is_active() const;
    bool is_post_round() const;
    bool ended() const;
    bool bomb_is_planted() const;
    Physics::Vector2D get_bomb_position() const;


    void update(int frames_to_process);

    void notify_on_one_player_less(Model::TeamID team);
    void notify_player_joined(Model::TeamID team);

    void notify_bomb_planted(Physics::Vector2D position);
    bool notify_bomb_is_being_defused(uint8_t player_id);
    void notify_bomb_is_not_longer_being_defused();
    void notify_bomb_exploded();
    bool bomb_is_being_defused() const;
    int player_id_defusing_bomb() const;
    bool get_bomb_exploded() const;

    void add_dropped_weapon(const DroppedWeapon& drop);
    std::vector<DroppedWeapon>& get_dropped_weapons();

    DTO::RoundDTO to_dto() const;
};

#endif  // ROUND_H
