#ifndef CLIENT_GAME_DEFINITIONS_H
#define CLIENT_GAME_DEFINITIONS_H

#include <memory>
#include <chrono>

#include "common/queue.h"

using ms = std::chrono::milliseconds;
using time_point = std::chrono::steady_clock::time_point;

template <typename T>
using ThreadSafe = std::shared_ptr<T>;

template <typename T>
using TS = ThreadSafe<T>;

template <typename T, typename... Args>
ThreadSafe<T> make_TS(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}


template <typename T>
using TSQueue = Queue<TS<T>>;

#endif // CLIENT_GAME_DEFINITIONS_H
