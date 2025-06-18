#include "smart_pane.h"

#include "controller/base_controller.h"

void View::SmartPane::position_children() {}

View::SmartPane::SmartPane(Weak<Controller::BaseController> controller):
        View::Pane(controller), View::Aligner(0.5f, 0.5f) {}

void View::SmartPane::render() {
    position_children();
    View::Pane::render();
}
