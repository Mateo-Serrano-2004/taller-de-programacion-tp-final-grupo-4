#include "pane_scalator.h"

#include <SDL2pp/Point.hh>

#include "entity/pane.h"

void View::PaneScalator::scalate_height_with_aspect_ratio(Pane* pane, int new_height) {
    auto size = pane->get_size();
    if (size.GetX() == 0)
        return;
    float aspect_ratio = ((float)(size.GetY())) / ((float)(size.GetX()));
    int new_width = (int)(new_height / aspect_ratio);
    pane->set_size(SDL2pp::Point(new_width, new_height));
}

void View::PaneScalator::scalate_width_with_aspect_ratio(Pane* pane, int new_width) {
    auto size = pane->get_size();
    if (size.GetX() == 0)
        return;
    float aspect_ratio = ((float)(size.GetY())) / ((float)(size.GetX()));
    int new_height = aspect_ratio * new_width;
    pane->set_size(SDL2pp::Point(new_width, new_height));
}
