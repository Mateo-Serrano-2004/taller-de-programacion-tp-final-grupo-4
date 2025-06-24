#include "pane.h"

#include <SDL2/SDL.h>
#include <SDL2pp/Color.hh>
#include <SDL2pp/Optional.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>

#include "asset/asset_manager.h"
#include "controller/base_controller.h"

void View::Pane::render_texture(Shared<SDL2pp::Texture> texture) {
    SDL2pp::Point absolute_position = get_absolute_position();
    renderer->Copy(*texture, texture_slice, SDL2pp::Rect(absolute_position, size), angle,
                   rotation_point);
}

View::Pane::Pane(Weak<Controller::BaseController> controller):
        View::Rendered(controller),
        View::Textured(controller),
        View::Rotated(0),
        position_set(false),
        size_set(false),
        draw_background(false),
        background(asset_manager->generate_background(SDL2pp::Color(0, 0, 0, 255))),
        position(0, 0),
        size(renderer->GetLogicalSize()),
        parent(nullptr) {}

bool View::Pane::get_draw_background() const { return draw_background; }

Shared<SDL2pp::Texture> View::Pane::get_background() const { return background; }

SDL2pp::Point View::Pane::get_position() const { return position; }

int View::Pane::get_x() const { return position.GetX(); }

int View::Pane::get_y() const { return position.GetY(); }

SDL2pp::Point View::Pane::get_size() const { return size; }

int View::Pane::get_height() const { return size.GetY(); }

int View::Pane::get_width() const { return size.GetX(); }

SDL2pp::Point View::Pane::get_absolute_position() const {
    if (!parent)
        return position;

    SDL2pp::Point parent_position = parent->get_absolute_position();

    return SDL2pp::Point(parent_position.GetX() + position.GetX(),
                         parent_position.GetY() + position.GetY());
}

View::Pane* View::Pane::get_parent() const { return parent; }

void View::Pane::set_draw_background(bool new_draw_background) {
    draw_background = new_draw_background;
}

void View::Pane::set_background_color(const SDL2pp::Color& new_color) {
    background = asset_manager->generate_background(new_color);
}

void View::Pane::set_background_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    background = asset_manager->generate_background(red, green, blue, alpha);
}

void View::Pane::set_position(const SDL2pp::Point& new_position) {
    position = new_position;
    position_set = true;
}

void View::Pane::set_x(int new_x) {
    position.SetX(new_x);
    position_set = true;
}

void View::Pane::set_y(int new_y) {
    position.SetY(new_y);
    position_set = true;
}

void View::Pane::set_width(int new_width) {
    size.SetX(new_width);
    size_set = true;
}

void View::Pane::set_height(int new_height) {
    size.SetY(new_height);
    size_set = true;
}

void View::Pane::set_size(const SDL2pp::Point& new_size) {
    size = new_size;
    size_set = true;
}

void View::Pane::set_parent(View::Pane* new_parent) {
    parent = new_parent;
    if (parent) {
        if (!position_set)
            position = parent->get_position();
        if (!size_set)
            size = parent->get_size();
    } else {
        if (!position_set)
            position = SDL2pp::Point(0, 0);
        if (!size_set)
            size = renderer->GetLogicalSize();
    }
}

void View::Pane::add_child(Pane* new_child) {
    children.push_back(new_child);
    new_child->set_parent(this);
}

void View::Pane::clear_children() { children.clear(); }

void View::Pane::render() {
    if (draw_background && background)
        render_texture(background);
    if (draw_texture && texture)
        render_texture(texture);

    for (auto& child: children) {
        child->render();
    }
}
