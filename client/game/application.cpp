#include "application.h"

#include <cstdint>
#include <exception>
#include <iostream>

#include <SDL2/SDL.h>

#include "common/periodic_clock.h"
#include "exception/closed_window.h"

App::Application::Application(): sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO) {}

void App::Application::launch() {
    bool keep_running = true;
    PeriodicClock clock(40);

    while (keep_running) {
        try {
            uint8_t frames = clock.sleep_and_get_frames();
            context_manager->update_current_context(frames);
            controller->handle_events();
        } catch (const App::ClosedWindowException& e) {
            keep_running = false;
        }
    }
}
