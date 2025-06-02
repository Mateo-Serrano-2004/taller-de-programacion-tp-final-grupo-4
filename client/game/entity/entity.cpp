#include "entity.h"

View::Entity::Entity(coord_t x, coord_t y) 
    : position(x, y), on_click(nullptr) {}

View::Entity::Entity(coord_t x, coord_t y, Callback on_click)
    : position(x, y), on_click(std::move(on_click)) {}

Physics::Vector2D View::Entity::get_position() const {
    return position;
}

void View::Entity::set_position(coord_t x, coord_t y) {
    position.set_x(x);
    position.set_y(y);
}

void View::Entity::set_callback(Callback new_callback) {
    on_click = std::move(new_callback);
}

void View::Entity::trigger_callback() {
    if (on_click) {
        on_click();
    }
}
