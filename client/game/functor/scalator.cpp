#include "scalator.h"

Scalator::Scalator()
: max_bounds(2, 2), min_bounds(1, 1), max_size(2, 2), min_size(1, 1) {}

Scalator::Scalator(SDL2pp::Point max_bounds, SDL2pp::Point min_bounds, SDL2pp::Point max_size,
                   SDL2pp::Point min_size):
        max_bounds(max_bounds), min_bounds(min_bounds), max_size(max_size), min_size(min_size) {}

void Scalator::set_max_bounds(const SDL2pp::Point& new_bounds) {
    max_bounds = new_bounds;
}

void Scalator::set_min_bounds(const SDL2pp::Point& new_bounds) {
    min_bounds = new_bounds;
}

void Scalator::set_max_size(const SDL2pp::Point& new_size) {
    max_size = new_size;
}

void Scalator::set_min_size(const SDL2pp::Point& new_size) {
    min_size = new_size;
}
