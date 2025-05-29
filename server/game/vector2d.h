#ifndef VECTOR2D_H
#define VECTOR2D_H

struct Vector2D {
    int x;
    int y;

    explicit Vector2D(int x = 0, int y = 0): x(x), y(y) {}

    Vector2D operator+(const Vector2D& other) const { return {x + other.x, y + other.y}; }

    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    bool operator==(const Vector2D& other) const { return x == other.x && y == other.y; }

    bool operator!=(const Vector2D& other) const { return !(*this == other); }
};

#endif  // VECTOR2D_H
