#include "button.h"

#include <utility>

#include <SDL2/SDL.h>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Color.hh>

#include "controller/base_controller.h"

View::Button::Button(Weak<Controller::BaseController> controller,
                     View::Pane* parent):
                     View::Pane(controller, parent),
                     command(nullptr),
                     controller(controller) {}

bool View::Button::check_click(Shared<SDL_Event> event) const {
    if (event->type != SDL_MOUSEBUTTONDOWN) return false;

    SDL2pp::Rect position = get_absolute_position();

    int x = event->button.x, y = event->button.y;

    if (x < position.GetX() ||
        y < position.GetY() ||
        x > position.GetX() + position.GetW() ||
        y > position.GetY() + position.GetH()) {
        return false;
    }

    return true;
}

void View::Button::set_command(Unique<Command::BaseCommand> new_command) {
    command = std::move(new_command);
    if (!command->is_executable()) command->set_controller(controller);
}

bool View::Button::trigger(Shared<SDL_Event> event) {
    bool triggered_event = check_click(event);
    if (triggered_event) {
        command->execute();
    }
    return triggered_event;
}
