#ifndef SERVER_GAME_VECTOR_2D_H
#define SERVER_GAME_VECTOR_2D_H

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
    Vector2D& operator+=(const Vector2D& other);
    bool operator==(const Vector2D& other) const;
    bool operator!=(const Vector2D& other) const;

    ~Vector2D() = default;
};
};

#endif  // SERVER_GAME_VECTOR_2D_H
