#ifndef CLIENT_GAME_CLOCK_H
#define CLIENT_GAME_CLOCK_H

#include <chrono>

#include "common/definitions.h"

namespace Model {
    class Clock {

    public:
        class Time {
            friend Clock;

            protected:
                time_point time;

                explicit Time(time_point time) : time(time) {}

            public:
                Time() = default;

                int64_t operator -(const Time& other) const {
                    return static_cast<int64_t>(
                        std::chrono::duration_cast<ms>(time - other.time)
                        .count()
                    );
                }

                Time& operator +=(int64_t amount) {
                    time += ms(amount);
                    return *this;
                }

                ~Time() = default;
            };

        Clock() = default;

        Time now();

        ~Clock() = default;
    };
};

#endif // CLIENT_GAME_CLOCK_H
