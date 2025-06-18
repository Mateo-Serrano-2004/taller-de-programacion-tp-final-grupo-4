#include "rotated.h"

#include <SDL2pp/Optional.hh>
#include <SDL2pp/Point.hh>

View::Rotated::Rotated(angle_t angle): angle(angle) {}

angle_t View::Rotated::get_angle() const { return angle; }

SDL2pp::Optional<SDL2pp::Point> View::Rotated::get_rotation_point() const { return rotation_point; }

void View::Rotated::set_angle(angle_t new_angle) { angle = new_angle; }

void View::Rotated::set_rotation_point(const SDL2pp::Point& new_point) {
    rotation_point = new_point;
}

void View::Rotated::reset_rotation_point() { rotation_point = SDL2pp::NullOpt; }
