#include "button.h"

#include <SDL2/SDL.h>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include "controller/base_controller.h"

bool View::Button::check_click(Shared<SDL_Event> event) const {
    if (event->type != SDL_MOUSEBUTTONDOWN) return false;

    SDL2pp::Rect position = get_absolute_position();

    int x = event->button.x, y = event->button.y;

    if (
        x < position.GetX() ||
        y < position.GetY() ||
        x > position.GetX() + position.GetW() ||
        y > position.GetY() + position.GetH()
    ) {
        return false;
    }

    return true;
}

View::Button::Button(Model::TextureID texture_id, Weak<Controller::BaseController> controller,
                     Pane* parent):
                     View::Pane(texture_id, controller, parent),
                     callback(controller) {}

View::Button::Button(Model::TextureID texture_id, Weak<Controller::BaseController> controller):
                     View::Pane(texture_id, controller),
                     callback(controller) {}

void View::Button::on_click(std::function<void(Weak<Controller::BaseController>)> callback) {
    this->callback.set_callback(callback);
}

bool View::Button::trigger(Shared<SDL_Event> event) {
    bool triggered_event = check_click(event);
    if (triggered_event) callback();
    return triggered_event;
}
