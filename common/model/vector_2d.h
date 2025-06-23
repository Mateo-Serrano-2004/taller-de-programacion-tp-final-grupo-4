#ifndef SERVER_GAME_VECTOR_2D_H
#define SERVER_GAME_VECTOR_2D_H

#include <cmath>
#include <utility>

#include "common/definitions.h"

namespace Physics {

class Vector2D {
private:
    coord_t x;
    coord_t y;

public:
    Vector2D();
    Vector2D(coord_t x, coord_t y);

    coord_t get_x() const;
    coord_t get_y() const;

    void set_x(coord_t new_x);
    void set_y(coord_t new_y);

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D& operator+=(const Vector2D& other);
    bool operator==(const Vector2D& other) const;
    bool operator!=(const Vector2D& other) const;

    Vector2D operator*(float scalar) const;
    float distance_to(const Vector2D& other) const;
    std::pair<float, float> normalized() const;

    static bool segments_intersect(const Vector2D& p1, const Vector2D& p2, const Vector2D& q1,
                                   const Vector2D& q2);

    ~Vector2D() = default;
};

}  // namespace Physics

#endif  // SERVER_GAME_VECTOR_2D_H
