
#ifndef PERIODIC_CLOCK_H
#define PERIODIC_CLOCK_H

#include <chrono>
#include <cstdint>

using steady_clock = std::chrono::steady_clock;
using time_point = steady_clock::time_point;
using ms = std::chrono::milliseconds;

class PeriodicClock {
private:
    uint64_t rate;
    time_point start;

public:
    explicit PeriodicClock(uint16_t fps);

    uint64_t sleep_and_get_frames();
};

#endif  // PERIODIC_CLOCK_H
