#include "round.h"
#include <iostream>

Round::Round(int ct_alive, int tt_alive)
    : winner_team(Model::TeamID::NONE),
      state(RoundState::Buying),
      number_of_ct_alive(ct_alive),
      number_of_tt_alive(tt_alive),
      bomb_planted(false),
      bomb_defused(false),
      bomb_position(0, 0),
      ticks_for_warmup_phase(0),
      ticks_for_buying_phase(600),
      ticks_for_playing_phase(3600),
      bomb_total_ticks(600),
      active_ticks_remaining(600),
      defusing_ticks(300),
      defusing_ticks_remaining(300),
      bomb_being_defused(false),
      player_defusing_bomb(-1),
      is_warmup_round(false) {}

Round Round::create_warmup_round() {
    Round r(0, 0);
    r.state = RoundState::Warmup;
    r.ticks_for_warmup_phase = 90;
    r.active_ticks_remaining = 90;
    r.is_warmup_round = true;
    return r;
}

void Round::update_if_finished_warmup() {
    state = RoundState::Ended;
    active_ticks_remaining = 0;
}

void Round::update_if_finished_buying() {
    state = RoundState::Active;
    active_ticks_remaining = ticks_for_playing_phase;
}

void Round::update_if_finished_playing() {
    if (bomb_planted && !bomb_defused){
        winner_team = Model::TeamID::TT;
    } else {
        winner_team = Model::TeamID::CT;
    }
    state = RoundState::Ended;
}

void Round::check_if_finished_defusing(int frames_to_process) {
    if (bomb_being_defused && !bomb_defused && bomb_planted) {

        if (active_ticks_remaining >= defusing_ticks_remaining) {

            defusing_ticks_remaining -= frames_to_process;

            if(defusing_ticks_remaining <= 0){
                bomb_defused = true;
                active_ticks_remaining = 0;
            }
        }
    }
}

void Round::update(int frames_to_process) {
    if (state == RoundState::Ended) return;

    check_if_finished_defusing(frames_to_process);

    if (active_ticks_remaining > frames_to_process) {
        active_ticks_remaining -= frames_to_process;
        return;
    }

    active_ticks_remaining = 0;

    if (state == RoundState::Warmup) {
        update_if_finished_warmup();
    } else if (state == RoundState::Buying) {
        update_if_finished_buying();
    } else if (state == RoundState::Active) {
        update_if_finished_playing();
    }
}

Model::TeamID Round::get_winner_team() const {
    return winner_team;
}

RoundState Round::get_state() const { return state; }

bool Round::is_warmup() const {
    return state == RoundState::Warmup;
}

bool Round::is_buying() const {
    return state == RoundState::Buying;
}

bool Round::is_active() const {
    return state == RoundState::Active;
}

bool Round::ended() const {
    return state == RoundState::Ended;
}

bool Round::bomb_is_planted() const {
    return bomb_planted;
}

void Round::notify_on_one_player_less(Model::TeamID team) {
    if (state == RoundState::Ended || state == RoundState::Warmup) return;

    if (team == Model::TeamID::CT) {
        number_of_ct_alive--;
        if (number_of_ct_alive == 0) {
            winner_team = Model::TeamID::TT;
            active_ticks_remaining = 0;
            state = RoundState::Ended;
        }
    } else if (team == Model::TeamID::TT) {
        number_of_tt_alive--;
        if (number_of_tt_alive == 0 && !bomb_planted) {
            winner_team = Model::TeamID::CT;
            active_ticks_remaining = 0;
            state = RoundState::Ended;
        }
    }
}

void Round::notify_player_joined(Model::TeamID team) {
    if (team == Model::TeamID::CT) number_of_ct_alive++;
    else if (team == Model::TeamID::TT) number_of_tt_alive++;
}

void Round::notify_bomb_planted(Physics::Vector2D position) {
    if (!is_active() || bomb_planted) return;
    bomb_planted = true;
    bomb_position = position;
    active_ticks_remaining = bomb_total_ticks;
}

bool Round::notify_bomb_is_being_defused(uint8_t player_id) {
    if (!bomb_planted || bomb_defused || !is_active()) return false;
    bomb_being_defused = true;
    player_defusing_bomb = player_id; // ojo int y uint
    return bomb_being_defused;
}

void Round::notify_bomb_is_not_longer_being_defused() {
    if (!bomb_planted || bomb_defused || !is_active()) return;
    defusing_ticks_remaining = defusing_ticks;
    bomb_being_defused = false;
    player_defusing_bomb = -1; // ojo int y uint
}

int Round::player_id_defusing_bomb() const {
    if (!bomb_planted || !bomb_being_defused || bomb_defused || !is_active()) return -1;
    return player_defusing_bomb;
}

DTO::RoundDTO Round::to_dto(int fps) const {
    
    uint8_t defuse_progress = 0;

    if (bomb_being_defused && bomb_planted && !bomb_defused && is_active()) {
        defuse_progress = static_cast<uint8_t>((defusing_ticks - defusing_ticks_remaining) * 100 / defusing_ticks);
    }

    return DTO::RoundDTO(
        state,
        this->ended(),
        this->get_ticks_remaining() / fps,
        this->get_winner_team(),
        this->bomb_planted,
        this->bomb_defused,
        this->bomb_position,
        defuse_progress
    );
}

int Round::get_ticks_remaining() const {
    return active_ticks_remaining;
}

bool Round::bomb_is_being_defused() const {
    return bomb_being_defused;
}