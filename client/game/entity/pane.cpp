#include "pane.h"

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Optional.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Texture.hh>

#include "controller/base_controller.h"
#include "asset/asset_manager.h"

View::Pane::Pane(Weak<Controller::BaseController> controller, Pane* parent):
        View::Rendered(controller),
        background_id(Model::BackgroundID::NO_BACKGROUND),
        position(SDL2pp::NullOpt),
        parent(parent) {}

Model::BackgroundID View::Pane::get_background_id() const { return background_id; }

bool View::Pane::has_position() const { return (bool) position; }

SDL2pp::Rect View::Pane::get_position() const {
    return position ? *position : get_parent_position();
}

SDL2pp::Rect View::Pane::get_absolute_position() const {
    if (!parent) return position ? *position : renderer->GetViewport();

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

void View::Pane::set_background(Model::BackgroundID new_background_id) {
    background_id = new_background_id;
    if (background_id != Model::BackgroundID::NO_BACKGROUND) {
        background = asset_manager->get_background(background_id);
    }
}

void View::Pane::set_position(const SDL2pp::Rect& new_position) {
    position = new_position;
}

void View::Pane::set_auto_fit() {
    position = parent ? parent->get_position() : renderer->GetViewport();
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

void View::Pane::render() {
    SDL2pp::Rect absolute_position = get_absolute_position();

    renderer->Copy(
        *background,
        texture_slice,
        absolute_position
    );

    if (draw_texture) {
        renderer->Copy(
            *texture,
            texture_slice,
            absolute_position
        );
    }
}
