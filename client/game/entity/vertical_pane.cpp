#include "vertical_pane.h"

#include "controller/base_controller.h"

void View::VerticalPane::position_children() {
    int total_height = children.empty() ? 0 : (children.size() - 1) * gap_y;

    for (auto child: children) {
        total_height += child->get_height();
    }

    int previous_start = (int) ((get_height() - total_height) * alignment_y);

    for (auto child: children) {
        child->set_x((int) ((get_width() - child->get_width()) * alignment_x));
        child->set_y(previous_start);
        previous_start += child->get_height();
        previous_start += gap_y;
    }
}

View::VerticalPane::VerticalPane(
    Weak<Controller::BaseController> controller,
    int gap_y
): View::SmartPane(controller),
   View::Gapped(gap_y, 0) {}
