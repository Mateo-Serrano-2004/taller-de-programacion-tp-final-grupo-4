#include "switch_context_event.h"

#include "common/event_type.h"

Model::SwitchContextEvent::SwitchContextEvent(const std::string& new_context_name):
        Model::Event(Model::EventType::SWITCH_CONTEXT), new_context_name(new_context_name) {}

const std::string& Model::SwitchContextEvent::get_new_context_name() const {
    return new_context_name;
}
