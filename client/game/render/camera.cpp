#include "camera.h"

#include <SDL2pp/Point.hh>

View::Camera::Camera(): viewport_width(0), viewport_height(0) {}

View::Camera::Camera(coord_t viewport_width, coord_t viewport_height):
        viewport_width(viewport_width), viewport_height(viewport_height) {}

View::Camera::Camera(const Camera& other):
        center(other.center),
        viewport_width(other.viewport_width),
        viewport_height(other.viewport_height) {}

SDL2pp::Point View::Camera::get_viewport() const {
    return SDL2pp::Point(viewport_width, viewport_height);
}

coord_t View::Camera::get_viewport_width() const { return viewport_width; }

coord_t View::Camera::get_viewport_height() const { return viewport_height; }

SDL2pp::Point View::Camera::get_center() const { return center; }

SDL2pp::Point View::Camera::get_camera_view(const Physics::Vector2D& point) const {
    return SDL2pp::Point(point.get_x() - center.x + (viewport_width / 2),
                         point.get_y() - center.y + (viewport_height / 2));
}

SDL2pp::Point View::Camera::get_camera_view(const SDL2pp::Point& point) const {
    return SDL2pp::Point(point.GetX() - center.x + (viewport_width / 2),
                         point.GetY() - center.y + (viewport_height / 2));
}

void View::Camera::set_viewport_width(coord_t new_width) { viewport_width = new_width; }

void View::Camera::set_viewport_height(coord_t new_height) { viewport_height = new_height; }

void View::Camera::set_viewport_size(coord_t new_width, coord_t new_height) {
    viewport_width = new_width;
    viewport_height = new_height;
}

void View::Camera::set_center(const SDL2pp::Point& new_center) { center = new_center; }

void View::Camera::set_center(coord_t x, coord_t y) { center = SDL2pp::Point(x, y); }
