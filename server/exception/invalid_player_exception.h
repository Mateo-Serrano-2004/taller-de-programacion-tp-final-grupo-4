#ifndef SERVER_GAME_EXCEPTION_INVALID_PLAYER_H
#define SERVER_GAME_EXCEPTION_INVALID_PLAYER_H

#include <exception>
#include <string>

class InvalidPlayerException: public std::exception {
private:
    std::string message;

public:
    explicit InvalidPlayerException(const std::string& message): message(message) {}

    const char* what() const noexcept override { return message.c_str(); };

    ~InvalidPlayerException() override = default;
};

#endif  // SERVER_GAME_EXCEPTION_INVALID_PLAYER_H
