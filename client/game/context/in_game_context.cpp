#include "in_game_context.h"

#include <cstdint>
#include <functional>
#include <memory>

#include <SDL2/SDL.h>

#include "common/event_type.h"
#include "common/model/player.h"
#include "controller/game_controller.h"
#include "exception/closed_window.h"

void Context::InGameContext::render(uint8_t frames) {
    player_renderer.render(frames);
    hud_renderer.render(frames);
}

void Context::InGameContext::dispatch_events() {
    while (SDL_PollEvent(&placeholder)) {
        event_handler_strategy.handle(make_shared<SDL_Event>(placeholder));
    }

    event_handler_strategy.handle_current_game_state();
}

Context::InGameContext::InGameContext(Weak<Controller::GameController> controller):
        Context::BaseContext("in-game", controller),
        player_renderer(controller),
        hud_renderer(controller),
        event_handler_strategy(controller) {}
