#include "common/model/vector_2d.h"

#include <algorithm>
#include <utility>

namespace Physics {

Vector2D::Vector2D(): x(0), y(0) {}
Vector2D::Vector2D(coord_t x, coord_t y): x(x), y(y) {}

coord_t Vector2D::get_x() const { return x; }
coord_t Vector2D::get_y() const { return y; }

void Vector2D::set_x(coord_t new_x) { x = new_x; }
void Vector2D::set_y(coord_t new_y) { y = new_y; }

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(x + other.get_x(), y + other.get_y());
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D(x - other.get_x(), y - other.get_y());
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
    x += other.get_x();
    y += other.get_y();
    return *this;
}

bool Vector2D::operator==(const Vector2D& other) const {
    return x == other.get_x() && y == other.get_y();
}

bool Vector2D::operator!=(const Vector2D& other) const { return !(*this == other); }

Vector2D Vector2D::operator*(float scalar) const { return Vector2D(x * scalar, y * scalar); }

float Vector2D::distance_to(const Vector2D& other) const {
    float dx = static_cast<float>(x - other.get_x());
    float dy = static_cast<float>(y - other.get_y());
    return std::sqrt(dx * dx + dy * dy);
}

std::pair<float, float> Vector2D::normalized() const {
    float length = std::sqrt(static_cast<float>(x) * x + static_cast<float>(y) * y);
    if (length == 0.0f)
        return std::make_pair(0.0f, 0.0f);
    return std::make_pair<float, float>(x / length, y / length);
}

static int orientation(const Vector2D& a, const Vector2D& b, const Vector2D& c) {
    int val = (b.get_y() - a.get_y()) * (c.get_x() - b.get_x()) -
              (b.get_x() - a.get_x()) * (c.get_y() - b.get_y());
    return (val > 0) - (val < 0);
}

static bool on_segment(const Vector2D& p, const Vector2D& q, const Vector2D& r) {
    return q.get_x() <= std::max(p.get_x(), r.get_x()) &&
           q.get_x() >= std::min(p.get_x(), r.get_x()) &&
           q.get_y() <= std::max(p.get_y(), r.get_y()) &&
           q.get_y() >= std::min(p.get_y(), r.get_y());
}

bool Vector2D::segments_intersect(const Vector2D& p1, const Vector2D& p2, const Vector2D& q1,
                                  const Vector2D& q2) {
    int o1 = orientation(p1, p2, q1);
    int o2 = orientation(p1, p2, q2);
    int o3 = orientation(q1, q2, p1);
    int o4 = orientation(q1, q2, p2);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && on_segment(p1, q1, p2))
        return true;
    if (o2 == 0 && on_segment(p1, q2, p2))
        return true;
    if (o3 == 0 && on_segment(q1, p1, q2))
        return true;
    if (o4 == 0 && on_segment(q1, p2, q2))
        return true;

    return false;
}

}  // namespace Physics
