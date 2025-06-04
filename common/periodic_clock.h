#ifndef CLIENT_GAME_PERIODIC_CLOCK_H
#define CLIENT_GAME_PERIODIC_CLOCK_H

#include <cstdint>

#include "definitions.h"

class PeriodicClock {
private:
    uint64_t rate;
    time_point start;

public:
    explicit PeriodicClock(uint16_t fps);

    uint64_t sleep_and_get_frames();
};

#endif  // CLIENT_GAME_PERIODIC_CLOCK_H
