#include "horizontal_pane.h"

#include <algorithm>

#include <SDL2pp/Rect.hh>

#include "controller/base_controller.h"

void View::HorizontalPane::position_children() {
    int total_width = children.empty() ? 0 : (children.size() - 1) * gap;

    for (auto child: children) {
        total_width += child->get_position().GetW();
    }

    int previous_start = (get_position().GetW() - total_width) / 2;

    for (size_t i = 0; i < children.size(); i++) {
        auto children_pos = children_positions[i];
        children_positions[i].SetX(previous_start);
        children_positions[i].SetY((get_position().GetH() - children_pos.GetH()) / 2);
        previous_start += children_pos.GetW();
        previous_start += gap;
        children[i]->set_position(children_positions[i]);
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
    children_positions.push_back(new_child->get_position());
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
