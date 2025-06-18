#include "end_of_game_context.h"

#include <cstdint>

#include <SDL2/SDL.h>

#include "controller/game_controller.h"

#include "event/quit_event.h"

void Context::EndOfGameContext::render(uint8_t) {
    background.render();
}

void Context::EndOfGameContext::dispatch_events() {
    while (SDL_PollEvent(&placeholder)) {
        if (placeholder.type == SDL_QUIT) {
            controller.lock()->push_event(make_shared<Model::QuitEvent>());
        }
    }
}

Context::EndOfGameContext::EndOfGameContext(Weak<Controller::BaseController> controller)
: Context::BaseContext("end-of-game", controller),
  background(controller),
  label(controller) {
    background.add_child(&label);
    background.set_background_color(122, 0, 0, 255);
    background.set_draw_background(true);

    label.set_text("END OF GAME");
    label.set_padding(10);
    label.set_background_color(0, 0, 0, 255);
    label.set_draw_background(true);
}
