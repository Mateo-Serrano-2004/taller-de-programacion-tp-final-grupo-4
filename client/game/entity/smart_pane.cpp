#include "smart_pane.h"

#include "controller/base_controller.h"

View::SmartPane::SmartPane(Weak<Controller::BaseController> controller)
: View::Pane(controller) {}

void View::SmartPane::add_child(View::Pane* new_child) {
    children.push_back(new_child);
    new_child->set_parent(this);
}

void View::SmartPane::render() {
    position_children();
    View::Pane::render();
    for (auto child: children) {
        child->render();
    }
}
