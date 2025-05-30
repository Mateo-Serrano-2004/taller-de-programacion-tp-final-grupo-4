#include "periodic_clock.h"

#include <cstdint>
#include <functional>
#include <chrono>
#include <thread>

#include "common/definitions.h"

PeriodicClock::PeriodicClock(uint16_t fps, std::function<void()> on_tick) {
    bool running = true;
    uint64_t frame = 0;
    uint64_t rate = (uint64_t) (1000 / fps);
    int64_t rest_time = 0;
    uint64_t behind = 0;
    uint64_t lost = 0;
    time_point end;
    time_point start = steady_clock::now();

    while (running) {
        on_tick();
        end = steady_clock::now();
        rest_time = rate - duration_cast<ms>(end - start).count();
        if (rest_time < 0) {
            behind = -rest_time;
            rest_time = rate - (behind % rate);
            lost = behind + rest_time;
            start += ms(lost);
            frame += (uint64_t) (lost / rate);
        }
        std::this_thread::sleep_for(ms(rest_time));
        start += ms(rate);
    }
}