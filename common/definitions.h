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
#include <functional>
#include <initializer_list>
#include <memory>
#include <optional>
#include <string>
#include <tuple>

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


// Colors
using color_tuple = std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>;
using font_tuple = std::tuple<std::string, uint8_t>;

// Utils
template <typename T>
using Maybe = std::optional<T>;

template <typename T>
using Ref = std::reference_wrapper<T>;

template <typename T>
using IList = std::initializer_list<T>;

// Events
template <typename T>
using Func = std::function<void(T)>;

constexpr int TILE_SIZE = 32;
const int BOMB_ZONE_RADIUS = 32;
const int DEFUSE_RADIUS = 32;
const int GAME_FPS = 60;

#endif  // COMMON_DEFINITIONS_H
