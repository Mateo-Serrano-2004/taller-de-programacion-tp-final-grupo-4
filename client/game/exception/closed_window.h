#ifndef CLIENT_GAME_EXCEPTION_CLOSED_WINDOW_H
#define CLIENT_GAME_EXCEPTION_CLOSED_WINDOW_H

#include <exception>
#include <string>

namespace App {
class ClosedWindowException: public std::exception {
private:
    std::string message;

public:
    explicit ClosedWindowException(const std::string& message): message(message) {}

    const char* what() const noexcept override { return message.c_str(); };

    ~ClosedWindowException() override = default;
};
}  // namespace App

#endif  // CLIENT_GAME_EXCEPTION_CLOSED_WINDOW_H
