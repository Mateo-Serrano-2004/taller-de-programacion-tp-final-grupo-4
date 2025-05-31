#ifndef CLIENT_GAME_HANDLER_SDL_EVENT_HANDLER_H
#define CLIENT_GAME_HANDLER_SDL_EVENT_HANDLER_H

#include <SDL2/SDL.h>

#include "common/definitions.h"
#include "common/thread.h"

#include "sdl_event_handler_strategy.h"

namespace Model {
class Event;
};

namespace Controller {
class SDLEventHandler: public Thread {
private:
    SharedQueue<Model::Event>* processor_event_queue;
    Shared<SDLEventHandlerStrategy> handler_strategy;
    SharedQueue<SDL_Event>* handler_strategy_queue;
    SDL_Event placeholder;

    void handle_quit_event();

public:
    SDLEventHandler(
        SharedQueue<Model::Event>* queue,
        Shared<SDLEventHandlerStrategy> strategy
    );

    void handle();

    void run() override;

    ~SDLEventHandler();
};
};  // namespace Controller

#endif  // CLIENT_GAME_HANDLER_SDL_EVENT_HANDLER_H
