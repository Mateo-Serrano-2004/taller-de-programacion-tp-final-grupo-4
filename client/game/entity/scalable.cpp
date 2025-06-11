#include "scalable.h"

#include <SDL2/SDL.h>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Point.hh>

void View::Scalable::scalate(const SDL2pp::Point& viewport) {
    if (!apply_scalation) return;
    current_size = scalator(viewport, keep_aspect_ratio);
}

View::Scalable::Scalable(
    SDL2pp::Point max_bounds, SDL2pp::Point min_bounds
): apply_scalation(false),
   keep_aspect_ratio(false),
   max_bounds(max_bounds),
   min_bounds(min_bounds),
   max_size(max_bounds),
   min_size(min_bounds),
   current_size(max_size),
   scalator(max_bounds, min_bounds, max_size, min_size) {}

SDL2pp::Point View::Scalable::get_max_bounds() const { return max_bounds; }

int View::Scalable::get_max_bounds_height() const { return max_bounds.GetY(); }

int View::Scalable::get_max_bounds_width() const { return max_bounds.GetX(); }

SDL2pp::Point View::Scalable::get_min_bounds() const { return min_bounds; }

int View::Scalable::get_min_bounds_height() const { return min_bounds.GetY(); }

int View::Scalable::get_min_bounds_width() const { return min_bounds.GetX(); }

SDL2pp::Point View::Scalable::get_max_size() const { return max_size; }

int View::Scalable::get_max_height() const { return max_size.GetY(); }

int View::Scalable::get_max_width() const { return max_size.GetX(); }

SDL2pp::Point View::Scalable::get_min_size() const { return min_size; }

int View::Scalable::get_min_height() const { return min_size.GetY(); }

int View::Scalable::get_min_width() const { return min_size.GetX(); }

SDL2pp::Point View::Scalable::get_size() const { return current_size; }

int View::Scalable::get_height() const { return current_size.GetY(); }

int View::Scalable::get_width() const { return current_size.GetX(); }

void View::Scalable::set_apply_scalation(bool new_apply_scalation) {
    apply_scalation = new_apply_scalation;
}

void View::Scalable::set_keep_aspect_ratio(bool new_keep_aspect_ratio) {
    keep_aspect_ratio = new_keep_aspect_ratio;
}

void View::Scalable::set_max_bound(const SDL2pp::Point& new_bounds) {
    max_bounds = new_bounds;
    scalator.set_max_bounds(max_bounds);
}

void View::Scalable::set_max_bounds_height(int new_height) {
    max_bounds.SetY(new_height);
    scalator.set_max_bounds(max_bounds);
}

void View::Scalable::set_max_bounds_width(int new_width) {
    max_bounds.SetX(new_width);
    scalator.set_max_bounds(max_bounds);
}

void View::Scalable::set_min_bounds(const SDL2pp::Point& new_bounds) {
    min_bounds = new_bounds;
    scalator.set_max_bounds(min_bounds);
}

void View::Scalable::set_min_bounds_height(int new_height) {
    min_bounds.SetY(new_height);
    scalator.set_max_bounds(min_bounds);
}

void View::Scalable::set_min_bounds_width(int new_width) {
    min_bounds.SetX(new_width);
    scalator.set_max_bounds(min_bounds);
}

void View::Scalable::set_max_size(const SDL2pp::Point& new_bounds) {
    set_max_height(new_bounds.GetY());
    set_max_width(new_bounds.GetX());
}

void View::Scalable::set_max_height(int new_height) {
    max_size.SetY(new_height);
    if (current_size.GetY() > new_height) current_size.SetY(new_height);
    scalator.set_max_size(max_size);
}

void View::Scalable::set_max_width(int new_width) {
    max_size.SetX(new_width);
    if (current_size.GetX() > new_width) current_size.SetX(new_width);
    scalator.set_max_size(max_size);
}

void View::Scalable::set_min_size(const SDL2pp::Point& new_bounds) {
    set_min_height(new_bounds.GetY());
    set_min_width(new_bounds.GetX());
}

void View::Scalable::set_min_height(int new_height) {
    min_size.SetY(new_height);
    if (current_size.GetY() < new_height) current_size.SetY(new_height);
    scalator.set_min_size(min_size);
}

void View::Scalable::set_min_width(int new_width) {
    min_size.SetX(new_width);
    if (current_size.GetX() < new_width) current_size.SetX(new_width);
    scalator.set_min_size(min_size);
}
