#include "menu_context.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2pp/Rect.hh>

#include "common/texture_id.h"

#include "controller/game_controller.h"
#include "controller/base_controller.h"
#include "exception/closed_window.h"
#include "event/quit_event.h"

void Context::MenuContext::render() {
    player_renderer.render();

    size_pane_relatively_to_parent(background, 0.6, 0.6);
    place_pane_relatively_to_parent(background, 0.5, 0.5);

    exit_button.set_position(SDL2pp::Rect(0, 0, 60, 40));

    place_pane_relatively_to_parent(exit_button, 0.5, 0.8);

    exit_button.set_texture_slice_to_match_position();

    background.render();
    exit_button.render();
}

void Context::MenuContext::dispatch_events() {
    while (SDL_PollEvent(&placeholder)) {
        auto event = make_shared<SDL_Event>(placeholder);

        exit_button.trigger(event);
        event_handler_strategy.handle(event);
    }
}

void Context::MenuContext::size_pane_relatively_to_parent(View::Pane& pane, double portion_x, double portion_y) {
    SDL2pp::Rect pane_position = pane.get_position();
    SDL2pp::Rect parent_position = pane.get_parent_position();

    pane.set_position(
        SDL2pp::Rect(
            pane_position.GetX(), pane_position.GetY(),
            (int) (parent_position.GetW() * portion_x),
            (int) (parent_position.GetH() * portion_y)
        )
    );
}

void Context::MenuContext::place_pane_relatively_to_parent(View::Pane& pane, double portion_x, double portion_y) {
    SDL2pp::Rect pane_position = pane.get_position();
    SDL2pp::Rect parent_position = pane.get_parent_position();

    int width = pane_position.GetW();
    int height = pane_position.GetH();

    int x = (parent_position.GetW() - width) * portion_x;
    int y = (parent_position.GetH() - height) * portion_y;

    pane.set_position(
        SDL2pp::Rect(x, y, width, height)
    );
}

Context::MenuContext::MenuContext(Weak<Controller::GameController> controller):
Context::BaseContext("menu", controller),
event_handler_strategy(controller),
player_renderer(controller),
background(Model::TextureID::BG_DARK_GREEN, controller),
exit_button(Model::TextureID::BG_SMOOTH_GREEN, controller, &background) {}
