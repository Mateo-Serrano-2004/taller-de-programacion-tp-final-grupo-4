#include "horizontal_pane.h"

#include "controller/base_controller.h"

void View::HorizontalPane::position_children() {
    int total_width = children.empty() ? 0 : (children.size() - 1) * gap_x;

    for (auto child: children) {
        total_width += child->get_width();
    }

    int previous_start = (int) ((get_width() - total_width) * alignment_x);

    for (auto child: children) {
        child->set_x(previous_start);
        child->set_y((int) ((get_height() - child->get_height()) * alignment_y));
        previous_start += child->get_width();
        previous_start += gap_x;
    }
}

View::HorizontalPane::HorizontalPane(
    Weak<Controller::BaseController> controller,
    int gap_x
): View::SmartPane(controller),
   View::Gapped(0, gap_x) {}
