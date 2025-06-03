#ifndef CLIENT_GAME_EVENT_WINDOW_RESIZE_EVENT_H
#define CLIENT_GAME_EVENT_WINDOW_RESIZE_EVENT_H

#include "event.h"

namespace Model {
class WindowResizeEvent: public Event {
public:
    WindowResizeEvent();

    ~WindowResizeEvent() override = default;
};
};

#endif // CLIENT_GAME_EVENT_WINDOW_RESIZE_EVENT_H
