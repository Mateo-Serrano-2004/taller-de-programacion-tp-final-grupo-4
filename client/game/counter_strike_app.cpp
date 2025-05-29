#include "counter_strike_app.h"

#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "client/net/client_protocol.h"
#include "common/definitions.h"
#include "exception/closed_window.h"

#include "clock.h"

const std::vector<std::string> paths = {"player/ct1.bmp", "player/ct2.bmp", "player/ct3.bmp",
                                        "player/ct4.bmp", "player/t1.bmp",  "player/t2.bmp",
                                        "player/t3.bmp",  "player/t4.bmp",  "player/vip.bmp"};

App::CounterStrikeApp::CounterStrikeApp(Net::ClientProtocol& protocol):
        protocol(protocol),
        game_state(protocol.receive_player_id()),
        sdl_controller(protocol, &sdl_window, &game_state),
        sdl_renderer(&sdl_window, &game_state, &texture_storage),
        texture_storage(&sdl_renderer) {
    for (size_t i = 0; i < paths.size(); i++) {
        texture_storage.load_texture(i, paths[i]);
    }

    run();
}

void App::CounterStrikeApp::run() {
    Model::Clock clock;
    bool running = true;
    Model::Clock::Time start = clock.now();
    uint64_t frame = 0;
    uint64_t rate = (uint64_t)(1000 / 40);  // 40 fps
    int64_t rest_time = 0;
    uint64_t behind = 0;
    uint64_t lost = 0;
    while (running) {
        try {
            sdl_controller.dispatch_events();
            sdl_renderer.render();
            Model::Clock::Time end = clock.now();
            rest_time = rate - (end - start);
            if (rest_time < 0) {
                behind = -rest_time;
                rest_time = rate - (behind % rate);
                lost = behind + rest_time;
                start += lost;
                frame += (int)(lost / rate);
            }
            std::this_thread::sleep_for(ms(rest_time));
            start += rate;
            frame++;
        } catch (...) {
            running = false;
        }
    }
}
