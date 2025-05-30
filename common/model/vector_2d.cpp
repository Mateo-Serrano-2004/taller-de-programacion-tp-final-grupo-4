#include "vector_2d.h"

Physics::Vector2D::Vector2D() : x(0), y(0) {}

Physics::Vector2D::Vector2D(coord_t x, coord_t y) : x(x), y(y) {}

coord_t Physics::Vector2D::get_x() const { return x; }

coord_t Physics::Vector2D::get_y() const { return y; }

void Physics::Vector2D::set_x(coord_t new_x) { x = new_x; }

void Physics::Vector2D::set_y(coord_t new_y) { y = new_y; }

Physics::Vector2D Physics::Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(x + other.get_x(), y + other.get_y());
}

Physics::Vector2D& Physics::Vector2D::operator+=(const Vector2D& other) {
    return *this = *this + other;
}

bool Physics::Vector2D::operator==(const Vector2D& other) const {
    return x == other.get_x() && y == other.get_y();
}

bool Physics::Vector2D::operator!=(const Vector2D& other) const {
    return x != other.get_x() || y != other.get_y();
}
