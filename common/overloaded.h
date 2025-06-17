#ifndef COMMON_OVERLOADED_H
#define COMMON_OVERLOADED_H

template <class... Ts>
struct overloaded: Ts... {
    using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

#endif  // COMMON_OVERLOADED_H
