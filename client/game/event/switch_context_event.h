#ifndef CLIENT_GAME_EVENT_SWITCH_CONTENT_EVENT_H
#define CLIENT_GAME_EVENT_SWITCH_CONTENT_EVENT_H

#include <string>

#include "event.h"

namespace Model {
class SwitchContextEvent: public Event {
protected:
    std::string new_context_name;

public:
    explicit SwitchContextEvent(const std::string& new_context_name);

    const std::string& get_new_context_name() const;

    ~SwitchContextEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_SWITCH_CONTENT_EVENT_H
