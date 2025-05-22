#include "clock.h"

Model::Clock::Time Model::Clock::now() {
    return Model::Clock::Time(std::chrono::steady_clock::now());
}
