#ifndef ROUND_H
#define ROUND_H

#include <cstdint>
#include <iostream>

enum class RoundState {
    NotStarted,
    Active,
    Ended
};

class Round {
private:
    RoundState state;
    uint64_t ticks_remaining;

public:
    explicit Round(uint64_t duration_in_ticks = 3600);  // default: 60s @ 60FPS

    void update();
    bool has_ended() const;
    RoundState get_state() const;
};

#endif // ROUND_H

