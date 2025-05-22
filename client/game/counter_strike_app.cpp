#include "counter_strike_app.h"

#include <vector>
#include <string>
#include <utility>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

#include "client/game/exception/closed_window.h"

const std::vector<std::string> paths = {
    "player/ct1.bmp",
    "player/ct2.bmp",
    "player/ct3.bmp",
    "player/ct4.bmp",
    "player/t1.bmp",
    "player/t2.bmp",
    "player/t3.bmp",
    "player/t4.bmp",
    "player/vip.bmp"
};

App::CounterStrikeApp::CounterStrikeApp()
: sdl_controller(&game_state),
   sdl_renderer(
    &sdl_window,
    &game_state,
    &texture_storage
), texture_storage(&sdl_renderer) {
    for (size_t i = 0; i < paths.size(); i++) {
        texture_storage.load_texture(i, paths[i]);
    }

    Model::Player p1(0, 0, 0);
    p1.set_skin_piece(0);
    Model::Player p2(64, 32, 1);
    p2.set_skin_piece(2);
    Model::Player p3(35, 60, 3);
    p3.set_skin_piece(4);

    game_state.register_player(std::move(p1));
    game_state.register_player(std::move(p2));
    game_state.register_player(std::move(p3));

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
