#include "button.h"

#include <utility>

#include <SDL2/SDL.h>
#include <SDL2pp/Color.hh>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include "controller/base_controller.h"

View::Button::Button(Weak<Controller::BaseController> controller):
        View::Label(controller), command(nullptr), controller(controller) {}

bool View::Button::check_click(Shared<SDL_Event> event) const {
    if (event->type != SDL_MOUSEBUTTONDOWN)
        return false;

    SDL2pp::Point position = get_absolute_position();

    int x = event->button.x, y = event->button.y;

    if (x < position.GetX() || y < position.GetY() || x > position.GetX() + get_width() ||
        y > position.GetY() + get_height()) {
        return false;
    }

    return true;
}

void View::Button::set_command(Unique<Command::BaseCommand> new_command) {
    command = std::move(new_command);
    if (!command->is_executable())
        command->set_controller(controller);
}

void View::Button::clear_command() { command.reset(); }

bool View::Button::trigger(Shared<SDL_Event> event) {
    bool triggered_event = check_click(event);
    if (triggered_event && command) {
        command->execute();
    }
    return triggered_event;
}
