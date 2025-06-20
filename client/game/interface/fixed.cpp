#include "fixed.h"

void Fixed::fix(const View::Camera& new_camera) { camera = new_camera; }

const View::Camera& Fixed::get_fixation() const { return camera; }
