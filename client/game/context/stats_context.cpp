#include "stats_context.h"

#include <string>

#include "controller/game_controller.h"
#include "handler/game_state_manager.h"
#include "model/game_state.h"

void Context::StatsContext::render(uint8_t frames) {
    auto game_state = game_state_manager->get_game_state();
    player_renderer.render(game_state, frames);
    hud_renderer.render(game_state, frames);

    stats_renderer.render(game_state);
    viewport.render();
}

void Context::StatsContext::dispatch_events() {
    strategy.dispatch();
    strategy.handle_current_game_state();
}

Context::StatsContext::StatsContext(Weak<Controller::GameController> controller):
        Context::BaseContext("stats", controller),
        player_renderer(controller),
        hud_renderer(controller),
        strategy(controller),
        game_state_manager(controller.lock()->get_game_state_manager()),
        viewport(controller),
        stats_renderer(controller, &viewport) {}
