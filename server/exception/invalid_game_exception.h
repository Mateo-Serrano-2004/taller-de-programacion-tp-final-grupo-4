#ifndef SERVER_GAME_EXCEPTION_INVALID_GAME_H
#define SERVER_GAME_EXCEPTION_INVALID_GAME_H

#include <exception>
#include <string>

class InvalidGameException: public std::exception {
private:
    std::string message;

public:
    explicit InvalidGameException(const std::string& message): message(message) {}

    const char* what() const noexcept override { return message.c_str(); };

    ~InvalidGameException() override = default;
};

#endif  // SERVER_GAME_EXCEPTION_INVALID_GAME_H
