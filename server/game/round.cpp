#include "round.h"

Round::Round(int ct_alive, int tt_alive, int duration_in_ticks, int buying_ticks, RoundState initial_state, bool is_warmup)
    : state(initial_state),
    buying_ticks_remaining(buying_ticks),
    active_ticks_remaining(duration_in_ticks),
    ct_alive(ct_alive),
    tt_alive(tt_alive),
    warmup(is_warmup) {}

Round::Round(int ct_alive, int tt_alive, int duration_in_ticks, int buying_ticks)
    : Round(ct_alive, tt_alive, duration_in_ticks, buying_ticks,
    RoundState::Buying, false) {}

Round Round::create_warmup_round() {
    std::cout << "RONDA WARMUP CREADA" << std::endl;
    return Round(0, 0, 300, 0, RoundState::Warmup, true);
}

void Round::update(int frames_to_process) {
    if (state == RoundState::Ended) return;

    if(state== RoundState::Warmup){
        if (frames_to_process < active_ticks_remaining) {
            active_ticks_remaining -= frames_to_process;
        } else {
            std::cout << "TERMINÓ RONDA WARMUP" << std::endl;
            active_ticks_remaining = 0;
            state = RoundState::Ended;
        }
    }
    
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
            // no contempla bomba por ahora
            std::cout << "Tiempo agotado: Ganan los CT\n";
            ct_won = true;
            state = RoundState::Ended;
        }
    }
}

Model::TeamID Round::which_team_won() const {
    if(ct_won) return Model::TeamID::CT;
    else if(tt_won) return Model::TeamID::TT;
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
