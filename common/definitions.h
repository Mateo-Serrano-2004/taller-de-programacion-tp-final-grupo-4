#ifndef COMMON_DEFINITIONS_H
#define COMMON_DEFINITIONS_H

#ifndef SUCCESS
#define SUCCESS 0
#endif // SUCCESS

#ifndef ERROR
#define ERROR 1
#endif // ERROR

#include <memory>
#include <chrono>

#include "queue.h"

using ms = std::chrono::milliseconds;
using time_point = std::chrono::steady_clock::time_point;

template <typename T>
using Shared = std::shared_ptr<T>;

using std::make_shared;

template <typename T>
using SharedQueue = Queue<Shared<T>>;

#endif // COMMON_DEFINITIONS_H
