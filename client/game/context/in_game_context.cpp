#include "in_game_context.h"

#include <functional>
#include <iostream>

#include <SDL2/SDL.h>

#include "common/event_type.h"
#include "common/model/player.h"

#include "handler/game_state_manager.h"
#include "controller/game_controller.h"
#include "entity/player.h"
#include "render/player_render_context.h"
#include "exception/closed_window.h"

void Context::InGameContext::render() {
    auto controller_locked = controller.lock();
    auto camera = game_state_manager->get_camera();

    View::PlayerRenderContext player_render_context(
        *(controller_locked->get_window().lock()),
        *(controller_locked->get_renderer().lock()),
        *(controller_locked->get_texture_storage().lock()),
        camera
    );

    game_state_manager->map_function_on_players(
        std::function<void(Model::Player&)>(
            [&](Model::Player& player) {
                View::Player view_player(player);
                view_player.render(player_render_context);
            }
        )
    );
}

void Context::InGameContext::dispatch_events() {
    while (SDL_PollEvent(&placeholder)) {
        processor_event_queue.push(make_shared<SDL_Event>(placeholder));

        if (placeholder.type == SDL_QUIT) {
            throw App::ClosedWindowException("Received a QUIT event");
        }
    }
}

Context::InGameContext::InGameContext(Weak<Controller::GameController> controller)
: Context::BaseContext("in-game", controller),
  running(true),
  event_handler_strategy(controller) {
    this->game_state_manager = controller.lock()->get_game_state_manager();
    start();
}

void Context::InGameContext::run() {
    bool running = true;
    while (running) {
        // Nor the main thread nor the event processor
        // closes the queue, so we can safely
        // call pop() without checking if the queue is closed.
        Shared<SDL_Event> event = processor_event_queue.pop();
        if (event->type == SDL_QUIT) {
            running = false;
        }
        event_handler_strategy.handle(event);
    }
}

Context::InGameContext::~InGameContext() {
    stop();
    join();
}
