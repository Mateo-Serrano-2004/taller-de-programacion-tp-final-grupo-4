#include "smart_pane.h"

#include "controller/base_controller.h"

View::SmartPane::SmartPane(Weak<Controller::BaseController> controller)
: View::Pane(controller),
  relative_height_percentage(0.5),
  relative_width_percentage(0.5) {}

void View::SmartPane::add_child(View::Pane* new_child) {
    children.push_back(new_child);
    new_child->set_parent(this);
}

void View::SmartPane::set_relative_height_position_percentage(float percentage) {
    relative_height_percentage = percentage;
}

void View::SmartPane::set_relative_width_position_percentage(float percentage) {
    relative_width_percentage = percentage;
}

void View::SmartPane::render() {
    position_children();
    View::Pane::render();
    for (auto child: children) {
        child->render();
    }
}
