#include "background.h"

#include "controller/base_controller.h"

View::Background::Background(
    short_id_t texture_id,
    Weak<Controller::BaseController> controller,
    View::Pane* parent
): View::Pane(texture_id, controller, parent) {}

View::Background::Background(short_id_t texture_id, Weak<Controller::BaseController> controller):
        View::Pane(texture_id, controller) {}
