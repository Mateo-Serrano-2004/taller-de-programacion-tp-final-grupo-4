#ifndef OVERLOADED_H
#define OVERLOADED_H

template <class... Ts>
struct overloaded: Ts... {
    using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

#endif  // OVERLOADED_H
