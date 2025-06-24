#include "pick_role_event_handler_strategy.h"

#include <memory>

#include "context/pick_role_context.h"
#include "controller/game_controller.h"

void Controller::PickRoleEventHandlerStrategy::handle_switch_context_event() {
    context->trigger_buttons(make_shared<SDL_Event>(current_event));
}

Controller::PickRoleEventHandlerStrategy::PickRoleEventHandlerStrategy(
        Weak<Controller::GameController> controller, Context::PickRoleContext* context):
        Controller::EventHandlerStrategy(controller), context(context) {}

void Controller::PickRoleEventHandlerStrategy::handle() {
    Controller::EventHandlerStrategy::handle();
    auto event_type = current_event.type;
    if (event_type == SDL_MOUSEBUTTONDOWN) {
        handle_switch_context_event();
    }
}
