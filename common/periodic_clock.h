
#ifndef PERIODIC_CLOCK_H
#define PERIODIC_CLOCK_H

#include <chrono>
#include <cstdint>

using steady_clock = std::chrono::steady_clock;
using time_point = steady_clock::time_point;
using ms = std::chrono::milliseconds;

class PeriodicClock {
public:
    explicit PeriodicClock(uint16_t fps);

    uint64_t sleep_and_get_frames();

private:
    uint64_t rate;
    time_point start;
};

#endif  // PERIODIC_CLOCK_H
/*#ifndef CLIENT_GAME_PERIODIC_CLOCK_H
#define CLIENT_GAME_PERIODIC_CLOCK_H

#include <cstdint>
#include <functional>

class PeriodicClock {
public:
    PeriodicClock(uint16_t fps, std::function<void(uint64_t)> on_tick);

    ~PeriodicClock() = default;
};

#endif  // CLIENT_GAME_PERIODIC_CLOCK_H*/

