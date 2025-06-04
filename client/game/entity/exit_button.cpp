#include "exit_button.h"

#include <utility>

#include "controller/base_controller.h"
#include "event/quit_event.h"

View::ExitButton::ExitButton(short_id_t texture_id, Weak<Controller::BaseController> controller,
                             Pane* parent)
                             : View::Button(texture_id, controller, parent) {
    on_click(
        [] (Weak<Controller::BaseController> controller) {
            auto quit_event = make_shared<Model::QuitEvent>();
            controller.lock()->handle_event(std::move(quit_event));
        }
    );
}

View::ExitButton::ExitButton(short_id_t texture_id, Weak<Controller::BaseController> controller)
                             : View::ExitButton(texture_id, controller, nullptr) {}
