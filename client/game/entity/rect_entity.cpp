#include "rect_entity.h"

View::RectEntity::RectEntity(coord_t x, coord_t y, length_t width, length_t height) 
    : Entity(x, y), width(width), height(height) {}

View::RectEntity::RectEntity(coord_t x, coord_t y, length_t width, length_t height, Callback on_click) 
    : Entity(x, y, on_click), width(width), height(height) {}

length_t View::RectEntity::get_width() const {
    return width;
}

length_t View::RectEntity::get_height() const {
    return height;
}

void View::RectEntity::set_width(length_t new_width) {
    width = new_width;
}

void View::RectEntity::set_height(length_t new_height) {
    height = new_height;
}
