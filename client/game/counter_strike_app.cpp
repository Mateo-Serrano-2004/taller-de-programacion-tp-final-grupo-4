#include "counter_strike_app.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "client/net/client_protocol.h"
#include "common/definitions.h"
#include "common/periodic_clock.h"
#include "exception/closed_window.h"


const std::vector<std::string> paths = {"player/ct1.bmp", "player/ct2.bmp", "player/ct3.bmp",
                                        "player/ct4.bmp", "player/t1.bmp",  "player/t2.bmp",
                                        "player/t3.bmp",  "player/t4.bmp",  "player/vip.bmp"};

void App::CounterStrikeApp::update() {
    sdl_controller.dispatch_events();
    sdl_renderer.render();
}

App::CounterStrikeApp::CounterStrikeApp(Net::ClientProtocol* protocol):
        protocol(protocol),
        game_state_manager(protocol->receive_player_id()),
        sdl_controller(protocol, &sdl_window, &game_state_manager),
        sdl_renderer(&sdl_window, &game_state_manager, &texture_storage),
        texture_storage(&sdl_renderer) {
    for (size_t i = 0; i < paths.size(); i++) {
        texture_storage.load_texture(i, paths[i]);
    }
}

void App::CounterStrikeApp::run() {
    try {
        PeriodicClock clock(40, [this]() { this->update(); });
    } catch (std::exception&) {
        std::cerr << "Exception during initialization";
    }
}
