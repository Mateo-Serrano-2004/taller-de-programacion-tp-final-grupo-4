#ifndef CLIENT_GAME_RENDER_SYNC_SDL_RENDERER_H
#define CLIENT_GAME_RENDER_SYNC_SDL_RENDERER_H

#include <list>
#include <string>

#include "sdl_renderer.h"
#include "../event/sdl_event.h"
#include "../utils/synchronized.h"

using namespace Abstract;

namespace View {
    class SyncSDLRenderer : public SDLRenderer,
                            public Synchronized<Controller::SDLEvent>
    {
    public:
        SyncSDLRenderer(
            App::SDLWindow* sdl_window,
            const std::list<std::string>& pathnames,
            TSQueue<Controller::SDLEvent>* queue
        ) : SDLRenderer(sdl_window, pathnames),
            Synchronized<Controller::SDLEvent>(queue) {}

        void render() override;

        ~SyncSDLRenderer() override = default;
    };
};

#endif // CLIENT_GAME_RENDER_SYNC_SDL_RENDERER_H
