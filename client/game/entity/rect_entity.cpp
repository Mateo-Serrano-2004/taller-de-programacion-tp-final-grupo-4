#include "rect_entity.h"

#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>

View::RectEntity::RectEntity(): View::Entity(), size(0, 0) {}

View::RectEntity::RectEntity(coord_t x, coord_t y, coord_t width, coord_t height):
        View::Entity(x, y), size(width, height) {}

View::RectEntity::RectEntity(const SDL2pp::Point& point, const SDL2pp::Point& size)
: View::Entity(point), size(size) {}

View::RectEntity::RectEntity(const SDL2pp::Rect& rect)
: View::Entity(rect.GetTopLeft()), size(rect.GetSize()) {}

coord_t View::RectEntity::get_width() const { return size.GetX(); }

coord_t View::RectEntity::get_height() const { return size.GetY(); }

SDL2pp::Point View::RectEntity::get_size() const { return size; }

SDL2pp::Rect View::RectEntity::get_rect() const { return SDL2pp::Rect(position, size); }

void View::RectEntity::set_width(coord_t new_width) {
    size.SetX(new_width);
}

void View::RectEntity::set_height(coord_t new_height) {
    size.SetY(new_height);
}

void View::RectEntity::set_size(const SDL2pp::Point& new_size) {
    size = new_size;
}

void View::RectEntity::set_rect(const SDL2pp::Rect& new_rect) {
    position = new_rect.GetTopLeft();
    size = new_rect.GetSize();
}
