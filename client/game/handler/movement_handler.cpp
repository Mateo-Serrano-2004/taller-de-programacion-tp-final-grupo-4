#include "movement_handler.h"

#include <memory>
#include <unordered_set>

#include <SDL2/SDL.h>

#include "common/definitions.h"
#include "controller/game_controller.h"
#include "event/movement_event.h"
#include "event/stop_movement_event.h"

void Controller::MovementHandler::set_up_handled_types() {
    handled_types.insert(SDL_KEYDOWN);
    handled_types.insert(SDL_KEYUP);

    handled_codes.insert(SDLK_w);
    handled_codes.insert(SDLK_a);
    handled_codes.insert(SDLK_s);
    handled_codes.insert(SDLK_d);
}

void Controller::MovementHandler::on_vertical_stop() {
    auto controller_locked = controller.lock();
    controller_locked->push_event(make_shared<Model::StopMovementEvent>(false));
    Controller::MovementHandler::moving_vertically = false;
}

void Controller::MovementHandler::on_horizontal_stop() {
    auto controller_locked = controller.lock();
    controller_locked->push_event(make_shared<Model::StopMovementEvent>(true));
    Controller::MovementHandler::moving_horizontally = false;
}

void Controller::MovementHandler::on_vertical_movement(const SDL_Event& event) {
    auto key = event.key.keysym.sym;
    auto controller_locked = controller.lock();
    controller_locked->push_event(make_shared<Model::MovementEvent>(0, key == SDLK_w ? -1 : 1));
    Controller::MovementHandler::moving_vertically = true;
}

void Controller::MovementHandler::on_horizontal_movement(const SDL_Event& event) {
    auto key = event.key.keysym.sym;
    auto controller_locked = controller.lock();
    controller_locked->push_event(make_shared<Model::MovementEvent>(key == SDLK_a ? -1 : 1, 0));
    Controller::MovementHandler::moving_horizontally = true;
}

void Controller::MovementHandler::update_movement_state(const SDL_Event& event) {
    auto key = event.key.keysym.sym;
    if (event.type == SDL_KEYDOWN) {
        if (!Controller::MovementHandler::moving_vertically && (key == SDLK_w || key == SDLK_s)) {
            on_vertical_movement(event);
        }
        if (!Controller::MovementHandler::moving_horizontally && (key == SDLK_a || key == SDLK_d)) {
            on_horizontal_movement(event);
        }
    } else {
        if (Controller::MovementHandler::moving_vertically && (key == SDLK_w || key == SDLK_s)) {
            on_vertical_stop();
        }
        if (Controller::MovementHandler::moving_horizontally && (key == SDLK_a || key == SDLK_d)) {
            on_horizontal_stop();
        }
    }
}

Controller::MovementHandler::MovementHandler(Weak<GameController> controller):
        Controller::GameHandler(controller) {
    set_up_handled_types();
}

void Controller::MovementHandler::handle(const SDL_Event& event) {
    if (can_handle(event)) {
        update_movement_state(event);
    }
}

bool Controller::MovementHandler::can_handle(const SDL_Event& event) {
    return handled_types.find(event.type) != handled_types.end() &&
           handled_codes.find(event.key.keysym.sym) != handled_codes.end();
}

void Controller::MovementHandler::stop() {
    if (Controller::MovementHandler::moving_horizontally)
        on_horizontal_stop();
    if (Controller::MovementHandler::moving_vertically)
        on_vertical_stop();
}
