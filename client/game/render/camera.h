#ifndef CLIENT_GAME_RENDER_CAMERA_H
#define CLIENT_GAME_RENDER_CAMERA_H

#include <SDL2pp/Point.hh>

#include "common/model/vector_2d.h"

namespace View {
class Camera {
protected:
    SDL2pp::Point center;
    length_t viewport_width;
    length_t viewport_height;

public:
    Camera();
    Camera(length_t viewport_width, length_t viewport_height);

    SDL2pp::Point get_viewport() const;
    length_t get_viewport_width() const;
    length_t get_viewport_height() const;
    void set_viewport_width(length_t new_width);
    void set_viewport_height(length_t new_height);
    void set_viewport_size(length_t new_width, length_t new_height);

    SDL2pp::Point get_center() const;
    void set_center(const SDL2pp::Point& new_center);
    void set_center(length_t x, length_t y);

    SDL2pp::Point get_camera_view(const Physics::Vector2D& point) const;

    Camera(const Camera&) = default;
    Camera& operator=(const Camera&) = default;
    Camera(Camera&&) = default;
    Camera& operator=(Camera&&) = default;

    ~Camera() = default;
};
};

#endif // CLIENT_GAME_RENDER_CAMERA_H
