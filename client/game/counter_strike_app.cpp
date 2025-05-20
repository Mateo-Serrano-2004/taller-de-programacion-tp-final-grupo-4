#include "client/game/counter_strike_app.h"

#include <list>
#include <string>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

#include "client/game/exception/closed_window.h"

App::CounterStrikeApp::CounterStrikeApp(const std::list<std::string>& images)
: sdl_renderer(
    &sdl_window,
    images,
    sdl_controller.get_queue()
) {
    run();
}

void App::CounterStrikeApp::run() {
    bool running = true;
    while (running) {
        try {
            sdl_controller.dispatch_events();
            sdl_renderer.render();
        } catch (ClosedWindowException& exception) {
            running = false;
        }
    }
}
