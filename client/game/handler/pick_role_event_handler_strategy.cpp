#include "pick_role_event_handler_strategy.h"

#include "context/pick_role_context.h"
#include "controller/game_controller.h"

void Controller::PickRoleEventHandlerStrategy::handle_switch_context_event(
        Shared<SDL_Event> event) {
    context->trigger_buttons(event);
}

Controller::PickRoleEventHandlerStrategy::PickRoleEventHandlerStrategy(
        Weak<Controller::GameController> controller, Context::PickRoleContext* context):
        Controller::EventHandlerStrategy(controller), context(context) {}

void Controller::PickRoleEventHandlerStrategy::handle(Shared<SDL_Event> event) {
    Controller::EventHandlerStrategy::handle(event);
    auto event_type = event->type;
    if (event_type == SDL_MOUSEBUTTONDOWN) {
        handle_switch_context_event(event);
    }
}
