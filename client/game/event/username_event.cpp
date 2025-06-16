#include "username_event.h"

#include <string>

Model::UsernameEvent::UsernameEvent(const std::string& username):
        Model::TransferedEvent(Model::EventType::USERNAME), username(username) {}

std::string Model::UsernameEvent::get_username() const { return username; }

DTO::EventDTO Model::UsernameEvent::as_dto() {
    return DTO::DTOCreatorVisitor::visit_username_event(this);
}
