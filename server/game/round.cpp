#include "round.h"

Round::Round(int ct_alive, int tt_alive, int duration_in_ticks, int buying_ticks, RoundState initial_state, bool is_warmup)
    : state(initial_state),
    buying_ticks_remaining(buying_ticks),
    active_ticks_remaining(duration_in_ticks),
    ct_alive(ct_alive),
    tt_alive(tt_alive),
    warmup(is_warmup) {}

Round::Round()
: state(RoundState::Warmup),
  buying_ticks_remaining(0),
  active_ticks_remaining(3600),
  ct_alive(0),
  tt_alive(0),
  warmup(true) {}

Round::Round(int ct_alive, int tt_alive, int duration_in_ticks, int buying_ticks):
        Round(ct_alive, tt_alive, duration_in_ticks, buying_ticks, RoundState::Buying, false) {}

bool Round::is_warmup() const { return state == RoundState::Warmup; }

bool Round::is_buying() const { return state == RoundState::Buying; }

bool Round::is_active() const { return state == RoundState::Active; }

bool Round::ended() const { return state == RoundState::Ended; }

void Round::update(int frames_to_process) {
    if (ended()) return;

    if (is_warmup()) {
        if (frames_to_process < active_ticks_remaining) {
            active_ticks_remaining -= frames_to_process;
        } else {
            std::cout << "TERMINÓ RONDA WARMUP" << std::endl;
            active_ticks_remaining = 0;
            state = RoundState::Buying;
        }
    }
    
    if (is_buying()) {
        if (frames_to_process < buying_ticks_remaining) {
            buying_ticks_remaining -= frames_to_process;
            return;
        } else {
            frames_to_process -= buying_ticks_remaining;
            buying_ticks_remaining = 0;
            state = RoundState::Active;
        }
    }
    
    if (is_active()) {
        if (frames_to_process < active_ticks_remaining) {
            active_ticks_remaining -= frames_to_process;
        } else {
            active_ticks_remaining = 0;
            // no contempla bomba por ahora
            std::cout << "Tiempo agotado: Ganan los CT\n";
            ct_won = true;
            state = RoundState::Ended;
        }
    }
}

Model::TeamID Round::which_team_won() const {
    if (ct_won) return Model::TeamID::CT;
    else if (tt_won) return Model::TeamID::TT;
    else return Model::TeamID::NONE;
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

bool Round::was_warmup() const {
    return warmup;
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
            tt_won = true;
            state = RoundState::Ended;
        }
    } else if (team == Model::TeamID::TT) {
        if (--tt_alive <= 0) {
            // Si la bomba está plantada, NO debe terminar la ronda falta esa lógica
            ct_won = true;
            state = RoundState::Ended;
        }
    }
}

void Round::notify_player_joined(Model::TeamID team) {
    if (team == Model::TeamID::CT) ct_alive++;
    else if (team == Model::TeamID::TT) tt_alive++;
}

void Round::notify_player_left(Model::TeamID team) {
    if (team == Model::TeamID::CT) {
        if (--ct_alive <= 0) {
            tt_won = true;
            state = RoundState::Ended;
        }
    } else if (team == Model::TeamID::TT) {
        if (--tt_alive <= 0) {
            // Si la bomba está plantada, NO debe terminar la ronda falta esa lógica
            ct_won = true;
            state = RoundState::Ended;
        }
    }
}

DTO::RoundDTO Round::to_dto(int fps) const {
    return DTO::RoundDTO(
        state,
        this->has_ended(),
        this->get_ticks_remaining() / fps,
        this->which_team_won()
    );
}
