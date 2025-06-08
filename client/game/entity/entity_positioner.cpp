#include "entity_positioner.h"

#include <SDL2pp/Rect.hh>

#include "pane.h"

void View::EntityPositioner::size_pane_relatively_to_parent(
    View::Pane& pane,
    double portion_x,
    double portion_y
) {
    SDL2pp::Rect pane_position = pane.get_position();
    SDL2pp::Rect parent_position = pane.get_parent_position();

    pane.set_position(
        SDL2pp::Rect(
            pane_position.GetX(), pane_position.GetY(),
            (int) (parent_position.GetW() * portion_x),
            (int) (parent_position.GetH() * portion_y)
        )
    );
}

void View::EntityPositioner::place_pane_relatively_to_parent(
    View::Pane& pane,
    double portion_x,
    double portion_y
) {
    SDL2pp::Rect pane_position = pane.get_position();
    SDL2pp::Rect parent_position = pane.get_parent_position();

    int width = pane_position.GetW();
    int height = pane_position.GetH();

    int x = (parent_position.GetW() - width) * portion_x;
    int y = (parent_position.GetH() - height) * portion_y;

    pane.set_position(
        SDL2pp::Rect(x, y, width, height)
    );
}
