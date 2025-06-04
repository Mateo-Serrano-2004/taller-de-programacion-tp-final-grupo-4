#ifndef COMMON_DEFINITIONS_H
#define COMMON_DEFINITIONS_H

#ifndef SUCCESS
#define SUCCESS 0
#endif  // SUCCESS

#ifndef ERROR
#define ERROR 1
#endif  // ERROR

#include <chrono>
#include <cstdint>
#include <memory>
#include <functional>

#include "queue.h"

// Time
using ms = std::chrono::milliseconds;
using steady_clock = std::chrono::steady_clock;
using time_point = steady_clock::time_point;

// Memory
template <typename T>
using Shared = std::shared_ptr<T>;
template <typename T>
using Unique = std::unique_ptr<T>;
template <typename T>
using Weak = std::weak_ptr<T>;
using std::make_shared;
using std::make_unique;
template <typename T>
using SharedQueue = Queue<Shared<T>>;

// Integer datatypes
using coord_t = int32_t;
using angle_t = int16_t;
using short_id_t = uint8_t;
using signed_id_t = int8_t;
using long_id_t = uint16_t;


// Functions
using Callback = std::function<void()>;

#endif  // COMMON_DEFINITIONS_H
