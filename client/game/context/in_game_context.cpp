#include "in_game_context.h"

#include <functional>

#include <SDL2/SDL.h>

#include "common/event_type.h"
#include "common/model/player.h"

#include "controller/game_controller.h"

#include "asset/background_id.h"

#include "handler/game_state_manager.h"

#include "exception/closed_window.h"

void Context::InGameContext::render() {
    background.render();
    player_renderer.render();
}

void Context::InGameContext::dispatch_events() {
    while (SDL_PollEvent(&placeholder)) {
        event_handler_strategy.handle(make_shared<SDL_Event>(placeholder));
    }

    event_handler_strategy.handle_current_game_state(game_state_manager);
}

Context::InGameContext::InGameContext(Weak<Controller::GameController> controller)
: Context::BaseContext("in-game", controller),
  background(controller),
  player_renderer(controller),
  event_handler_strategy(controller),
  game_state_manager(controller.lock()->get_game_state_manager()) {
    background.set_background(Model::BackgroundID::BG_YELLOW);
}
