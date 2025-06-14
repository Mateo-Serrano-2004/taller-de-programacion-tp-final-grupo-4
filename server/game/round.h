#ifndef ROUND_H
#define ROUND_H

#include <cstdint>
#include <iostream>
#include "common/team.h"
#include "common/round_state.h"
#include "common/DTO/round_dto.h"

class Round {
private:
    RoundState state;
    int buying_ticks_remaining;
    int active_ticks_remaining;
    int ct_alive;
    int tt_alive;
    bool warmup = false;
    bool tt_won = false;
    bool ct_won = false;

    Round(int ct_alive, int tt_alive, int duration_in_ticks, int buying_ticks, RoundState initial_state, bool is_warmup);

public:
    explicit Round(int ct_alive, int tt_alive, int duration_in_ticks = 7200, int buying_ticks = 600);// default: 60s @ 60FPS

    static Round create_warmup_round();

    void update(int frames_to_process);
    bool has_ended() const;
    RoundState get_state() const;
    uint16_t get_ticks_remaining() const;
    bool is_buying_phase() const;
    bool is_active_phase() const;
    bool was_warmup() const;
    // Si la bomba está plantada, NO debe terminar la ronda falta esa lógica
    void notify_player_death(Model::TeamID team);
    void notify_player_joined(Model::TeamID team);
    void notify_player_left(Model::TeamID team);
    Model::TeamID which_team_won() const;
    DTO::RoundDTO to_dto(int fps) const;
};

#endif // ROUND_H

