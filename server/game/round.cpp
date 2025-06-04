#include "round.h"

Round::Round(int duration_in_ticks)
    : state(RoundState::Active), ticks_remaining(duration_in_ticks) {}

void Round::update(int frames_to_process) {
    if (state != RoundState::Active) return;

    if (ticks_remaining > 0) {
        ticks_remaining -= frames_to_process;
        if (ticks_remaining <= 0) {
            state = RoundState::Ended;
        }
    }
}

bool Round::has_ended() const {
    return state == RoundState::Ended;
}

uint16_t Round::get_ticks_remaining() const {
    if(state == RoundState::Ended){
        return 0;
    }
    return ticks_remaining;
}

RoundState Round::get_state() const {
    return state;
}
