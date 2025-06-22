#include "in_game_context.h"

#include <cstdint>
#include <functional>
#include <memory>

#include "common/event_type.h"
#include "common/model/player.h"
#include "controller/game_controller.h"
#include "event/switch_context_event.h"
#include "handler/game_state_manager.h"

void Context::InGameContext::render(uint8_t frames) {
    current_game_state = game_state_manager->get_game_state();
    player_renderer.render(current_game_state, frames);
    hud_renderer.render(current_game_state, frames);
}

void Context::InGameContext::dispatch_events() {
    strategy.dispatch();
    strategy.handle_current_game_state();
}

Context::InGameContext::InGameContext(Weak<Controller::GameController> controller):
        Context::BaseContext("in-game", controller),
        player_renderer(controller),
        hud_renderer(controller),
        strategy(controller, this),
        game_state_manager(controller.lock()->get_game_state_manager()) {}

void Context::InGameContext::notify_event(Shared<Model::Event> event) {
    if (event->get_type() == Model::EventType::SWITCH_CONTEXT) {
        auto switch_context_event = std::static_pointer_cast<Model::SwitchContextEvent>(event);
        strategy.update_on_switch_context(switch_context_event->get_new_context_name());
    }
}
