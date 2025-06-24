#include "mouse_movement_handler.h"

#include <memory>

#include <SDL2pp/Renderer.hh>

#include "controller/game_controller.h"
#include "event/rotation_event.h"
#include "utils/mouse_coords_translator.h"

Controller::MouseMovementHandler::MouseMovementHandler(Weak<GameController> controller):
        controller(controller), renderer(controller.lock()->get_renderer()) {}

void Controller::MouseMovementHandler::notify_current_rotation() {
    auto mouse_coords = MouseCoordsTranslator::get_logical_coords(renderer);

    SDL2pp::Point screen_size = renderer->GetLogicalSize();

    coord_t dy = mouse_coords.GetY() - (screen_size.GetY() / 2);
    coord_t dx = mouse_coords.GetX() - (screen_size.GetX() / 2);

    double angle_rad = std::atan2(dy, dx);
    double angle_deg = angle_rad * 180.0 / M_PI;

    angle_deg += 90;

    if (angle_deg < 0)
        angle_deg += 360;
    if (angle_deg >= 360)
        angle_deg -= 360;

    angle_t angle = static_cast<angle_t>(angle_deg);
    controller.lock()->push_event(make_shared<Model::RotationEvent>(angle));
}
