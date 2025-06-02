#include "application.h"

#include <SDL2/SDL.h>

#include "common/periodic_clock.h"

App::Application::Application()
: sdl(SDL_INIT_VIDEO) {}

void App::Application::launch() {
    PeriodicClock clock(
        60,
        [this] () { context_manager->update_current_context(); }
    );
}
