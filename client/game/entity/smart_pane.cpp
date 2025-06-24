#include "smart_pane.h"

#include <algorithm>

#include <SDL2pp/Point.hh>

#include "controller/base_controller.h"

void View::SmartPane::position_children() {}

void View::SmartPane::fit() {}

View::SmartPane::SmartPane(Weak<Controller::BaseController> controller):
        View::Pane(controller), View::Aligner(0.5f, 0.5f), fit_to_children(false) {}

void View::SmartPane::set_fit_to_children(bool new_fit) {
    size_set = true;
    fit_to_children = new_fit;
    if (fit_to_children) {
        fit();
    }
}

void View::SmartPane::add_child(View::Pane* new_child) {
    View::Pane::add_child(new_child);
    if (fit_to_children)
        fit();
}

void View::SmartPane::clear_children() {
    View::Pane::clear_children();
    if (fit_to_children)
        size = SDL2pp::Point(0, 0);
}

void View::SmartPane::render() {
    position_children();
    if (fit_to_children)
        fit();
    View::Pane::render();
}
