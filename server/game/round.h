#ifndef ROUND_H
#define ROUND_H

#include <cstdint>
#include <iostream>
#include "common/team.h"
#include "common/round_state.h"
#include "common/DTO/round_dto.h"

class Round {
private:
    Model::TeamID winner_team = Model::TeamID::NONE;
    int count_of_rounds = 0;

    RoundState state;
    int number_of_ct_alive;
    int number_of_tt_alive;

    // X seconds = N frames / M FPS
    // For 60FPS, X seconds = N frames / 60FPS
    int ticks_for_warmup_phase;
    int ticks_for_buying_phase;
    int ticks_for_playing_phase;

    int active_ticks_remaining;

    void update_if_finished_warmup();
    void update_if_finished_buying();
    void update_if_finished_playing();

public:
    // Builds a base round in warmup state
    Round();

    Model::TeamID get_winner_team() const;
    int get_count_of_rounds() const;
    RoundState get_state() const;
    bool is_warmup() const;
    bool is_buying() const;
    bool is_active() const;
    bool ended() const;
    uint16_t get_ticks_remaining() const;

    void set_ticks_for_warmup_phase(int ticks);
    void set_ticks_for_buying_phase(int ticks);
    void set_ticks_for_playing_phase(int ticks);

    void set_ct_count(int count);
    void set_tt_count(int count);

    void to_buying_phase();
    void update(int frames_to_process);

    // Si la bomba está plantada, NO debe terminar la ronda falta esa lógica
    void notify_on_one_player_less(Model::TeamID team);
    void notify_player_joined(Model::TeamID team);

    DTO::RoundDTO to_dto(int fps) const;
};

#endif // ROUND_H

