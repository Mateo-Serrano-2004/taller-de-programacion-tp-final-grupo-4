#include "loading_context.h"

#include "controller/game_controller.h"

void Context::LoadingContext::render(uint8_t) { viewport.render(); }

void Context::LoadingContext::dispatch_events() { strategy.dispatch(); }

Context::LoadingContext::LoadingContext(Weak<Controller::GameController> controller):
        Context::BaseContext("loading", controller),
        strategy(controller),
        viewport(controller),
        label(controller) {
    viewport.add_child(&label);
    viewport.set_horizontal_alignment(0.05f);
    viewport.set_vertical_alignment(0.95f);

    label.set_text("Loading...");
    label.set_font_size(35);
}
