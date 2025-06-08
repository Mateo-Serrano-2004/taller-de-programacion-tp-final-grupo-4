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
    int ticks_remaining;

public:
    explicit Round(int duration_in_ticks = 7200);  // default: 60s @ 60FPS

    void update(int frames_to_process);
    bool has_ended() const;
    RoundState get_state() const;
    uint16_t get_ticks_remaining() const;
};

#endif // ROUND_H
