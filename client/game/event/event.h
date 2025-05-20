#ifndef CLIENT_GAME_EVENTS_EVENT_H
#define CLIENT_GAME_EVENTS_EVENT_H

class Event {
private:
    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;
    Event(Event&&) = delete;
    Event& operator=(Event&&) = delete;

public:
    Event() = default;

    virtual ~Event() = default;
};

#endif // CLIENT_GAME_EVENTS_EVENT_H
