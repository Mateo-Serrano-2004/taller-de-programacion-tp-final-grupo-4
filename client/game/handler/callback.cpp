#include "callback.h"

#include <functional>

#include "controller/base_controller.h"

Controller::Callback::Callback(
    Weak<Controller::BaseController> controller
): Controller::Callback::Callback(controller, nullptr) {}

Controller::Callback::Callback(
    Weak<Controller::BaseController> controller,
    std::function<void(Weak<Controller::BaseController>)> callback
): controller(controller), callback(callback) {}

bool Controller::Callback::is_valid() const { return (bool) callback; }

void Controller::Callback::set_callback(
        std::function<void(Weak<Controller::BaseController>)> new_callback) {
            callback = new_callback;
        }
