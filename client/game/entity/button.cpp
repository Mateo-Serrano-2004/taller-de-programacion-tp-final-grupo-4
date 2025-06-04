#include "button.h"

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Texture.hh>

#include "controller/base_controller.h"

View::Button::Button(
    const SDL2pp::Rect& rect,
    short_id_t texture_id,
    Weak<Controller::BaseController> controller
): View::Rendered(texture_id, controller),
   View::RectEntity(rect) {}

void View::Button::render() {
    SDL2pp::Texture& texture = texture_storage->get_texture(texture_id);

    renderer->Copy(
        texture,
        SDL2pp::NullOpt,
        SDL2pp::Rect(position, size)
    );
};
