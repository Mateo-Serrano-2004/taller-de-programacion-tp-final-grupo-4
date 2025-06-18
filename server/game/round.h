#ifndef ROUND_H
#define ROUND_H

#include <cstdint>
#include <iostream>
#include "common/team.h"
#include "common/round_state.h"
#include "common/DTO/round_dto.h"
#include "common/model/vector_2d.h"

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
    int bomb_total_ticks;

    int active_ticks_remaining;

    bool is_warmup_round;

    void update_if_finished_warmup();
    void update_if_finished_buying();
    void update_if_finished_playing();

public:
    Round(int ct_alive, int tt_alive);

    static Round create_warmup_round();

    Model::TeamID get_winner_team() const;
    RoundState get_state() const;
    bool is_warmup() const;
    bool is_buying() const;
    bool is_active() const;
    bool ended() const;
    bool bomb_is_planted() const;

    void update(int frames_to_process);

    void notify_on_one_player_less(Model::TeamID team);
    void notify_player_joined(Model::TeamID team);

    void notify_bomb_planted(Physics::Vector2D position);
    void notify_bomb_defused();

    int get_ticks_remaining() const;

    DTO::RoundDTO to_dto(int fps) const;
};

#endif // ROUND_H

