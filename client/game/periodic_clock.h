#ifndef CLIENT_GAME_PERIODIC_CLOCK_H
#define CLIENT_GAME_PERIODIC_CLOCK_H

#include <cstdint>
#include <functional>

class PeriodicClock {
public:
    PeriodicClock(uint16_t fps, std::function<void()> on_tick);

    ~PeriodicClock() = default;
};

#endif // CLIENT_GAME_PERIODIC_CLOCK_H
