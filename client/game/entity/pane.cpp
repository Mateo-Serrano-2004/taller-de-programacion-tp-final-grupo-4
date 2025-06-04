#include "pane.h"

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Optional.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Texture.hh>

#include "controller/base_controller.h"
#include "texture/texture_storage.h"

View::Pane::Pane(short_id_t texture_id, Weak<Controller::BaseController> controller, Pane* parent):
        View::Rendered(texture_id, controller), parent(parent) {}

View::Pane::Pane(short_id_t texture_id, Weak<Controller::BaseController> controller):
        View::Pane(texture_id, controller, nullptr) {}

bool View::Pane::has_position() const { return (bool) position; }

SDL2pp::Rect View::Pane::get_position() const {
    return position ? *position : SDL2pp::Rect();
}

void View::Pane::set_position(const SDL2pp::Rect& new_position) {
    position = new_position;
}

void View::Pane::set_auto_fit() {
    position = SDL2pp::NullOpt;
}

SDL2pp::Rect View::Pane::get_texture_slice() const {
    return texture_slice ? *texture_slice : SDL2pp::Rect();
}

bool View::Pane::has_texture_slice() const { return (bool) texture_slice; }

void View::Pane::set_texture_slice(const SDL2pp::Rect& new_slice) {
    texture_slice = new_slice;
}

void View::Pane::set_full_texture() {
    texture_slice = SDL2pp::NullOpt;
}

void View::Pane::set_texture_slice_to_match_position() {
    texture_slice = position;
}

void View::Pane::set_parent(View::Pane* new_parent) {
    parent = new_parent;
}

SDL2pp::Rect View::Pane::get_absolute_position() const {
    if (!parent) return position ? *position : SDL2pp::Rect();

    SDL2pp::Rect parent_position = parent->get_absolute_position();
    SDL2pp::Rect displacement = get_position();

    return SDL2pp::Rect(
        parent_position.GetX() + displacement.GetX(),
        parent_position.GetY() + displacement.GetY(),
        displacement.GetW(),
        displacement.GetH()
    );
}

SDL2pp::Rect View::Pane::get_parent_position() const {
    return parent ? parent->get_position() : renderer->GetViewport();
}

void View::Pane::render() {
    SDL2pp::Texture& texture = texture_storage->get_texture(texture_id);

    SDL2pp::Rect absolute_position = get_absolute_position();

    renderer->Copy(
        texture,
        texture_slice,
        absolute_position
    );
}
