#include "window_resize_event.h"

#include "common/event_type.h"

Model::WindowResizeEvent::WindowResizeEvent()
: Model::Event(Model::EventType::WINDOW_RESIZE) {}
