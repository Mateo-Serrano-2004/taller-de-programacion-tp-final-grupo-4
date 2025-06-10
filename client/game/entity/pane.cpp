#include "pane.h"

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Optional.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Color.hh>

#include "controller/base_controller.h"
#include "asset/asset_manager.h"

View::Pane::Pane(Weak<Controller::BaseController> controller):
        View::Rendered(controller),
        draw_background(false),
        scale_size(false),
        position(0, 0),
        size(window->GetSize()),
        min_size(0, 0),
        max_size(window->GetSize()),
        parent(nullptr) {
    background = asset_manager->generate_background(SDL2pp::Color(0, 0, 0, 255));
}

bool View::Pane::get_draw_background() const { return draw_background; }

bool View::Pane::get_scale_size() const { return scale_size; }

Shared<SDL2pp::Texture> View::Pane::get_background() const { return background; }

SDL2pp::Point View::Pane::get_position() const { return position; }

SDL2pp::Point View::Pane::get_size() const { return size; }

SDL2pp::Point View::Pane::get_min_size() const { return min_size; }

SDL2pp::Point View::Pane::get_max_size() const { return max_size; }

int View::Pane::get_x() const {
    return position.GetX();
}

int View::Pane::get_y() const {
    return position.GetY();
}

int View::Pane::get_width() const {
    return size.GetX();
}

int View::Pane::get_height() const {
    return size.GetY();
}

SDL2pp::Point View::Pane::get_absolute_position() const {
    if (!parent) return position;

    SDL2pp::Point parent_position = parent->get_absolute_position();

    return SDL2pp::Point(
        parent_position.GetX() + position.GetX(),
        parent_position.GetY() + position.GetY()
    );
}

View::Pane* View::Pane::get_parent() const { return parent; }

void View::Pane::set_draw_background(bool new_draw_background) {
    draw_background = new_draw_background;
}

void View::Pane::set_scale_size(bool new_scale_size) {
    scale_size = new_scale_size;
}

void View::Pane::set_background_color(const SDL2pp::Color& new_color) {
    background = asset_manager->generate_background(new_color);
}

void View::Pane::set_background_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    background = asset_manager->generate_background(red, green, blue, alpha);
}

void View::Pane::set_position(const SDL2pp::Point& new_position) {
    position = new_position;
}

void View::Pane::set_x(int new_x) {
    position.SetX(new_x);
}

void View::Pane::set_y(int new_y) {
    position.SetY(new_y);
}

void View::Pane::set_width(int new_width) {
    int real_width = std::min(std::max(new_width, min_size.GetX()), max_size.GetX());
    size.SetX(real_width);
}

void View::Pane::set_height(int new_height) {
    int real_height = std::min(std::max(new_height, min_size.GetY()), max_size.GetY());
    size.SetY(real_height);
}

void View::Pane::set_size(const SDL2pp::Point& new_size) {
    set_width(new_size.GetX());
    set_height(new_size.GetY());
}

void View::Pane::set_min_size(const SDL2pp::Point& new_min_size) {
    min_size = new_min_size;
}

void View::Pane::set_min_width(int new_min_width) {
    min_size.SetX(new_min_width);
    set_width(size.GetX());
}

void View::Pane::set_min_height(int new_min_height) {
    min_size.SetY(new_min_height);
    set_height(size.GetY());
}

void View::Pane::set_max_size(const SDL2pp::Point& new_max_size) {
    max_size = new_max_size;
}

void View::Pane::set_max_width(int new_max_width) {
    max_size.SetX(new_max_width);
    set_width(size.GetX());
}

void View::Pane::set_max_height(int new_max_height) {
    max_size.SetY(new_max_height);
    set_height(size.GetY());
}

void View::Pane::set_scale_factor(float new_scale_factor) {
    size_scalator.set_factor(new_scale_factor);
}

void View::Pane::set_parent(View::Pane* new_parent) {
    parent = new_parent;
    if (parent) position = parent->get_position();
    else position = SDL2pp::Point(0, 0);
}

void View::Pane::center() {
    int parent_width = parent ? parent->get_width() : window->GetWidth();
    int parent_height = parent ? parent->get_height() : window->GetHeight();
    set_x((parent_width - get_width()) / 2);
    set_y((parent_height - get_height()) / 2);
}

void View::Pane::render() {
    if (scale_size) {
        auto scaled_size = size_scalator(parent ? parent->get_size() : window->GetSize());
        set_size(scaled_size);
    }

    SDL2pp::Point absolute_position = get_absolute_position();

    if (draw_background) {
        renderer->Copy(
            *background,
            texture_slice,
            SDL2pp::Rect(absolute_position, size)
        );
    }

    if (draw_texture) {
        renderer->Copy(
            *texture,
            texture_slice,
            SDL2pp::Rect(absolute_position, size)
        );
    }
}
