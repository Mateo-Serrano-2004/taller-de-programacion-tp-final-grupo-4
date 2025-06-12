#include "round.h"

Round::Round(int ct_alive, int tt_alive, int duration_in_ticks, int buying_ticks)
    : state(RoundState::Buying),
      ct_alive(ct_alive),
      tt_alive(tt_alive),
      buying_ticks_remaining(buying_ticks),
      active_ticks_remaining(duration_in_ticks) {}

void Round::update(int frames_to_process) {
    if (state == RoundState::Ended) return;
    
    if (state == RoundState::Buying) {
        if (frames_to_process < buying_ticks_remaining) {
            buying_ticks_remaining -= frames_to_process;
            return;
        } else {
            frames_to_process -= buying_ticks_remaining;
            buying_ticks_remaining = 0;
            state = RoundState::Active;
        }
    }
    
    if (state == RoundState::Active) {
        if (frames_to_process < active_ticks_remaining) {
            active_ticks_remaining -= frames_to_process;
        } else {
            active_ticks_remaining = 0;
            state = RoundState::Ended;
        }
    }
}

bool Round::has_ended() const {
    return state == RoundState::Ended;
}

bool Round::is_buying_phase() const {
    return state == RoundState::Buying;
}

bool Round::is_active_phase() const {
    return state == RoundState::Active;
}

uint16_t Round::get_ticks_remaining() const {
    if (state == RoundState::Ended) return 0;
    if (state == RoundState::Buying) return buying_ticks_remaining;
    return active_ticks_remaining;
}

RoundState Round::get_state() const {
    return state;
}

void Round::notify_player_death(Model::TeamID team) {
    if (team == Model::TeamID::CT) {
        if (--ct_alive <= 0) {
            state = RoundState::Ended;
        }
    } else if (team == Model::TeamID::TT) {
        if (--tt_alive <= 0) {
            // Si la bomba está plantada, NO debe terminar la ronda falta esa lógica
            state = RoundState::Ended;
        }
    }
}
