#include "periodic_clock.h"

#include <chrono>
#include <cstdint>
#include <functional>
#include <thread>

#include "definitions.h"

PeriodicClock::PeriodicClock(uint16_t fps): rate(1000 / fps), start(steady_clock::now()) {}

uint64_t PeriodicClock::sleep_and_get_frames() {
    time_point end = steady_clock::now();
    int64_t rest_time = rate - std::chrono::duration_cast<ms>(end - start).count();

    uint64_t frames_to_process;
    if (rest_time < 0) {
        uint64_t behind = -rest_time;
        rest_time = rate - (behind % rate);
        uint64_t lost = behind + rest_time;
        start += ms(lost);
        frames_to_process = (lost / rate) + 1;
    } else {
        frames_to_process = 1;
    }
    std::this_thread::sleep_for(ms(rest_time));
    start += ms(rate);

    return frames_to_process;
}
