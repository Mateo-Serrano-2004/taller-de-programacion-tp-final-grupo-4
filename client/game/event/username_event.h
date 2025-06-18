#ifndef CLIENT_EVENT_USERNAME_EVENT_H
#define CLIENT_EVENT_USERNAME_EVENT_H

#include <string>

#include "common/DTO/event_dto.h"
#include "dto_handler/dto_creator_visitor.h"

#include "transfered_event.h"

namespace Model {
class UsernameEvent: public TransferedEvent {
private:
    const std::string username;

public:
    explicit UsernameEvent(const std::string& username);

    std::string get_username() const;

    DTO::EventDTO as_dto() override;

    ~UsernameEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_EVENT_USERNAME_EVENT_H
