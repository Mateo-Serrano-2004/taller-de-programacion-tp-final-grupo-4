#ifndef CLIENT_GAME_ENTITY_ROTATED_H
#define CLIENT_GAME_ENTITY_ROTATED_H

#include <SDL2pp/Optional.hh>
#include <SDL2pp/Point.hh>

#include "common/definitions.h"

namespace View {
class Rotated {
protected:
    angle_t angle;
    SDL2pp::Optional<SDL2pp::Point> rotation_point;

public:
    explicit Rotated(angle_t angle = 0);

    angle_t get_angle() const;
    SDL2pp::Optional<SDL2pp::Point> get_rotation_point() const;

    void set_angle(angle_t new_angle);
    void set_rotation_point(const SDL2pp::Point& new_point);
    void reset_rotation_point();

    virtual ~Rotated() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_ENTITY_ROTATED_H
