#include "round.h"

void Round::update_if_finished_warmup() {
    std::cout << "Fin de la etapa de warmup" << std::endl;
    active_ticks_remaining = 0;
    state = RoundState::Ended;
}

void Round::update_if_finished_buying() {
    std::cout << "Fin de la etapa de compra\n";
    active_ticks_remaining = ticks_for_playing_phase;
    state = RoundState::Active;
}

void Round::update_if_finished_playing() {
    std::cout << "Tiempo agotado: Empate\n";

    // TODO: Implement logic bomb and update this part
    count_of_rounds++;
    active_ticks_remaining = 0;
    state = RoundState::Ended;
}

Round::Round()
: state(RoundState::Warmup),
  number_of_ct_alive(0),
  number_of_tt_alive(0),
  ticks_for_warmup_phase(600),
  ticks_for_buying_phase(600),
  ticks_for_playing_phase(3600),
  active_ticks_remaining(600) {}

Model::TeamID Round::get_winner_team() const {
    return winner_team;
}

int Round::get_count_of_rounds() const { return count_of_rounds; }

RoundState Round::get_state() const {
    return state;
}

bool Round::is_warmup() const { return state == RoundState::Warmup; }

bool Round::is_buying() const { return state == RoundState::Buying; }

bool Round::is_active() const { return state == RoundState::Active; }

bool Round::ended() const { return state == RoundState::Ended; }

uint16_t Round::get_ticks_remaining() const {
    return active_ticks_remaining;
}

void Round::set_ticks_for_warmup_phase(int ticks) {
    ticks_for_warmup_phase = ticks;
}

void Round::set_ticks_for_buying_phase(int ticks) {
    ticks_for_buying_phase = ticks;
}

void Round::set_ticks_for_playing_phase(int ticks) {
    ticks_for_playing_phase = ticks;
}

void Round::set_ct_count(int count) {
    number_of_ct_alive = count;
}

void Round::set_tt_count(int count) {
    number_of_tt_alive = count;
}

void Round::to_buying_phase() {
    active_ticks_remaining = ticks_for_buying_phase;
    state = RoundState::Buying;
}

void Round::update(int frames_to_process) {
    if (active_ticks_remaining > frames_to_process) {
        active_ticks_remaining -= frames_to_process;
        return;
    }

    if (is_warmup()) update_if_finished_warmup();
    else if (is_buying()) update_if_finished_buying();
    else if (is_active()) update_if_finished_playing();
}

void Round::notify_on_one_player_less(Model::TeamID team) {
    if (team == Model::TeamID::CT) {
        number_of_ct_alive--;
        if (number_of_ct_alive == 0) {
            winner_team = Model::TeamID::TT;
            state = RoundState::Ended;
            active_ticks_remaining = 0;
            count_of_rounds++;
        }
    } else if (team == Model::TeamID::TT) {
        number_of_tt_alive;
        if (number_of_tt_alive == 0) {
            // TOOD: Add bomb logic and prevent end of game if it is still planted

            winner_team = Model::TeamID::CT;
            state = RoundState::Ended;
            active_ticks_remaining = 0;
            count_of_rounds++;
        }
    }
}

void Round::notify_player_joined(Model::TeamID team) {
    // Note: Only CT and TT can reach this point
    if (team == Model::TeamID::CT) number_of_ct_alive++;
    else number_of_tt_alive++;
}

DTO::RoundDTO Round::to_dto(int fps) const {
    return DTO::RoundDTO(
        state,
        this->ended(),
        this->get_ticks_remaining() / fps,
        this->get_winner_team()
    );
}
