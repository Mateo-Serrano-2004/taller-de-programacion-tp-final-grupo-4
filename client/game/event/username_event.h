#ifndef CLIENT_EVENT_USERNAME_EVENT_H
#define CLIENT_EVENT_USERNAME_EVENT_H

#include <string>

#include "event.h"

namespace Model {
    class UsernameEvent : public Event {
    private:
        const std::string username;

    public:
        UsernameEvent(const std::string& username);

        std::string get_username() const;
        
        ~UsernameEvent() override = default;
    };
};

#endif // CLIENT_EVENT_USERNAME_EVENT_H
