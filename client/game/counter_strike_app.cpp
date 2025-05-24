#include "counter_strike_app.h"

#include <vector>
#include <string>
#include <utility>
#include <thread>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL.h>

#include "definitions.h"

#include "exception/closed_window.h"
#include "clock.h"

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

    Model::Player p1(0, 0, 0, 0, 0);
    p1.set_skin_piece(0);
    Model::Player p2(1, 64, 32, 0, 1);
    p2.set_skin_piece(2);
    Model::Player p3(2, 35, 60, 0, 3);
    p3.set_skin_piece(4);

    game_state.register_player(std::move(p1));
    game_state.register_player(std::move(p2));
    game_state.register_player(std::move(p3));

    run();
}

void App::CounterStrikeApp::run() {
    Model::Clock clock;
    bool running = true;
    Model::Clock::Time start = clock.now();
    uint64_t frame = 0;
    uint64_t rate = (uint64_t) (1000 / 30); // 30 fps
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
                frame += (int) (lost / rate);
            }
            std::this_thread::sleep_for(ms(rest_time));
            start += rate;
            frame++;
        } catch (ClosedWindowException& exception) {
            running = false;
        }
    }
}
