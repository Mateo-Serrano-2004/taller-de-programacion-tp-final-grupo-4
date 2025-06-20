#ifndef CLIENT_GAME_RENDER_CAMERA_H
#define CLIENT_GAME_RENDER_CAMERA_H

#include <SDL2pp/Point.hh>

#include "common/model/vector_2d.h"

namespace View {
class Camera {
protected:
    SDL2pp::Point center;
    coord_t viewport_width;
    coord_t viewport_height;

public:
    Camera();
    Camera(coord_t viewport_width, coord_t viewport_height);
    Camera(const Camera& other);

    SDL2pp::Point get_viewport() const;
    coord_t get_viewport_width() const;
    coord_t get_viewport_height() const;
    SDL2pp::Point get_center() const;
    SDL2pp::Point get_camera_view(const Physics::Vector2D& point) const;
    SDL2pp::Point get_camera_view(const SDL2pp::Point& point) const;

    void set_viewport_width(coord_t new_width);
    void set_viewport_height(coord_t new_height);
    void set_viewport_size(coord_t new_width, coord_t new_height);
    void set_center(const SDL2pp::Point& new_center);
    void set_center(coord_t x, coord_t y);

    Camera& operator=(const Camera& other) = default;

    ~Camera() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_RENDER_CAMERA_H
