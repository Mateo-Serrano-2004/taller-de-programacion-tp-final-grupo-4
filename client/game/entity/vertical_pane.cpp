#include "vertical_pane.h"

#include "controller/base_controller.h"

void View::VerticalPane::position_children() {
    int total_height = children.empty() ? 0 : (children.size() - 1) * gap;

    for (auto child: children) {
        total_height += child->get_height();
    }

    int previous_start = (get_height() - total_height) / 2;

    for (auto child: children) {
        child->set_x((get_width() - child->get_width()) / 2);
        child->set_y(previous_start);
        previous_start += child->get_height();
        previous_start += gap;
    }
}

View::VerticalPane::VerticalPane(Weak<Controller::BaseController> controller, int gap)
: View::SmartPane(controller), gap(gap) {}

int View::VerticalPane::get_gap() const {
    return gap;
}

void View::VerticalPane::set_gap(int new_gap) {
    gap = new_gap;
}
