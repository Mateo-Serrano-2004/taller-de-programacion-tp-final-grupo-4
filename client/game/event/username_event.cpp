#include "username_event.h"

#include <string>

Model::UsernameEvent::UsernameEvent(const std::string& username):
        Model::Event(Model::EventType::USERNAME), username(username) {}

std::string Model::UsernameEvent::get_username() const { return username; }
