#include "event.h"

Model::Event::Event(EventType type): type(type) {}

Model::EventType Model::Event::get_type() const { return type; }
