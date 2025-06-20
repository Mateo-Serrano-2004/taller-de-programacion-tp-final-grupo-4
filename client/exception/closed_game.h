#ifndef CLIENT_GAME_EXCEPTION_CLOSED_GAME_H
#define CLIENT_GAME_EXCEPTION_CLOSED_GAME_H

#include <exception>
#include <string>

class ClosedGameException: public std::exception {
private:
    std::string message;

public:
    explicit ClosedGameException(const std::string& message): message(message) {}

    const char* what() const noexcept override { return message.c_str(); };

    ~ClosedGameException() override = default;
};

#endif  // CLIENT_GAME_EXCEPTION_CLOSED_GAME_H
