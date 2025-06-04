#include "application.h"

#include <SDL2/SDL.h>

#include "common/periodic_clock.h"

App::Application::Application()
: sdl(SDL_INIT_VIDEO) {}

void App::Application::launch() {
    bool keep_running = true;
    PeriodicClock clock(60);

    while (keep_running) {
        try {
            (void) clock.sleep_and_get_frames();
            context_manager->update_current_context();
        } catch (...) {
            keep_running = true;
        }
    }
}
