#include "horizontal_pane.h"

#include <algorithm>

#include <SDL2pp/Point.hh>

#include "controller/base_controller.h"

void View::HorizontalPane::position_children() {
    int total_width = children.empty() ? 0 : (children.size() - 1) * gap;

    for (auto child: children) {
        total_width += child->get_width();
    }

    int previous_start = (get_width() - total_width) / 2;

    for (auto child: children) {
        child->set_x(previous_start);
        child->set_y((get_height() - child->get_height()) / 2);
        previous_start += child->get_width();
        previous_start += gap;
    }
}

View::HorizontalPane::HorizontalPane(Weak<Controller::BaseController> controller, int gap):
        View::Pane(controller), gap(gap) {}

void View::HorizontalPane::set_gap(int new_gap) {
    gap = new_gap;
    position_children();
}

void View::HorizontalPane::add_child(View::Pane* new_child) {
    children.push_back(new_child);
    new_child->set_parent(this);
    position_children();
}

int View::HorizontalPane::get_gap() const { return gap; }

void View::HorizontalPane::render() {
    View::Pane::render();
    std::for_each(
        children.begin(),
        children.end(),
        [] (View::Pane* child) {
            child->render();
        }
    );
}
