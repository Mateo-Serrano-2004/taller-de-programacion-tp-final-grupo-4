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
        position(0, 0),
        size(window->GetSize()),
        parent(nullptr) {}

Shared<SDL2pp::Texture> View::Pane::get_background() const { return background; }

SDL2pp::Point View::Pane::get_position() const { return position; }

SDL2pp::Point View::Pane::get_size() const { return size; }

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
    size.SetX(new_width);
}

void View::Pane::set_height(int new_height) {
    size.SetY(new_height);
}

void View::Pane::set_size(const SDL2pp::Point& new_size) {
    size = new_size;
}

void View::Pane::set_texture_slice_to_match_position() {
    texture_slice = SDL2pp::Rect(position, size);
}

void View::Pane::set_parent(View::Pane* new_parent) {
    parent = new_parent;
    if (parent) position = parent->get_position();
    else position = window->GetSize();
}

void View::Pane::center() {
    int parent_width = parent ? parent->get_width() : window->GetWidth();
    int parent_height = parent ? parent->get_height() : window->GetHeight();
    set_x((parent_width - get_width()) / 2);
    set_y((parent_height - get_height()) / 2);
}

void View::Pane::render() {
    SDL2pp::Point absolute_position = get_absolute_position();

    renderer->Copy(
        *background,
        texture_slice,
        SDL2pp::Rect(absolute_position, size)
    );

    if (draw_texture) {
        renderer->Copy(
            *texture,
            texture_slice,
            SDL2pp::Rect(absolute_position, size)
        );
    }
}
