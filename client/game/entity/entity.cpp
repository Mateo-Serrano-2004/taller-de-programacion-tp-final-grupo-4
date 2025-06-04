#include "entity.h"

#include <SDL2pp/Point.hh>

View::Entity::Entity(): position(0, 0) {}

View::Entity::Entity(coord_t x, coord_t y): position(x, y) {}

View::Entity::Entity(const SDL2pp::Point& point): position(point) {}

coord_t View::Entity::get_x() const {
    return position.GetX();
}

coord_t View::Entity::get_y() const {
    return position.GetY();
}

SDL2pp::Point View::Entity::get_position() const {
    return position;
}

void View::Entity::set_position(coord_t x, coord_t y) {
    position.SetX(x);
    position.SetY(y);
}

void View::Entity::set_position(const SDL2pp::Point& point) {
    position = point;
}
