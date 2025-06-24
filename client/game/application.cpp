#include "application.h"

#include <cstdint>
#include <exception>

#include <SDL2/SDL.h>

#include "client/exception/closed_game.h"
#include "common/periodic_clock.h"

void App::Application::launch() {
    bool keep_running = true;
    PeriodicClock clock(40);

    while (keep_running) {
        try {
            uint8_t frames = clock.sleep_and_get_frames();
            context_manager->update_current_context(frames);
            controller->handle_events();
        } catch (const ClosedGameException& e) {
            keep_running = false;
        }
    }
}
