#include "round.h"

Round::Round(uint64_t duration_in_ticks)
    : state(RoundState::Active), ticks_remaining(duration_in_ticks) {}

void Round::update() {
    if (state != RoundState::Active) return;

    if (ticks_remaining > 0) {
        --ticks_remaining;
        if (ticks_remaining <= 0) {
            state = RoundState::Ended;
        }
    }

    std::cout << "[RONDA] TICK " << ticks_remaining << std::endl;
}

bool Round::has_ended() const {
    return state == RoundState::Ended;
}

RoundState Round::get_state() const {
    return state;
}
