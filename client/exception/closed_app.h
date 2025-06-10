#ifndef CLIENT_GAME_EXCEPTION_CLOSED_APP_H
#define CLIENT_GAME_EXCEPTION_CLOSED_APP_H

#include <exception>
#include <string>

class ClosedAppException: public std::exception {
private:
    std::string message;

public:
    explicit ClosedAppException(const std::string& message): message(message) {}

    const char* what() const noexcept override { return message.c_str(); };

    ~ClosedAppException() override = default;
};

#endif  // CLIENT_GAME_EXCEPTION_CLOSED_APP_H
