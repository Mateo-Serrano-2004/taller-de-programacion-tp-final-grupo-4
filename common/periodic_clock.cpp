#include "periodic_clock.h"

#include <chrono>
#include <cstdint>
#include <functional>
#include <thread>

#include "definitions.h"

PeriodicClock::PeriodicClock(uint16_t fps)
    : rate(1000 / fps), start(steady_clock::now()) {}

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
        std::this_thread::sleep_for(ms(rest_time));
        start += ms(rate);
    }

    return frames_to_process;
}

/*PeriodicClock::PeriodicClock(uint16_t fps, std::function<void(uint64_t)> on_tick) {
    bool running = true;
    uint64_t frames_to_process = 1;
    uint64_t rate = (uint64_t)(1000 / fps);
    int64_t rest_time = 0;
    uint64_t behind = 0;
    uint64_t lost = 0;
    time_point end;
    time_point start = steady_clock::now();

    while (running) {
        try {
            on_tick(frames_to_process);
            end = steady_clock::now();
            rest_time = rate - duration_cast<ms>(end - start).count();
            if (rest_time < 0) {
                behind = -rest_time;
                rest_time = rate - (behind % rate);
                lost = behind + rest_time;
                start += ms(lost);
                frames_to_process = (uint64_t)(lost / rate) + 1;
            } else {
                frames_to_process = 1;
            }
            std::this_thread::sleep_for(ms(rest_time));
            start += ms(rate);
            
        } catch (std::exception&) {
            running = false;
        }
    }
}*/
