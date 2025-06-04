#include "background.h"

#include <algorithm>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

View::Background::Background(
    short_id_t texture_id,
    Weak<Controller::BaseController> controller
): View::Rendered(texture_id, controller),
   View::RectEntity(0, 0, window->GetWidth(), window->GetHeight()) {}

void View::Background::render() {
    SDL2pp::Texture& texture = texture_storage->get_texture(texture_id);
    int x, y, width, height;

    x = std::min(0, (texture.GetWidth() - window->GetWidth()) / 2);
    width = std::min(texture.GetWidth(), window->GetWidth());

    y = std::min(0, (texture.GetHeight() - window->GetHeight()) / 2);
    height = std::min(texture.GetHeight(), window->GetHeight());

    renderer->Copy(
        texture,
        SDL2pp::Rect(x, y, width, height),
        SDL2pp::NullOpt
    );
}
