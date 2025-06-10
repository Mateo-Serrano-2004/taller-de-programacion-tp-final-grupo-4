#ifndef ROUND_H
#define ROUND_H

#include <cstdint>
#include <iostream>

enum class RoundState {
    Buying,
    Active,
    Ended
};

class Round {
private:
    RoundState state;
    int buying_ticks_remaining;
    int active_ticks_remaining;

public:
    explicit Round(int duration_in_ticks = 7200, int buying_ticks = 600);  // default: 60s @ 60FPS

    void update(int frames_to_process);
    bool has_ended() const;
    RoundState get_state() const;
    uint16_t get_ticks_remaining() const;
    bool is_buying_phase() const;
    bool is_active_phase() const;
};

#endif // ROUND_H

