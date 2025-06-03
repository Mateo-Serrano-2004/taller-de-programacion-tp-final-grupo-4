#include "menu_renderer.h"

#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Color.hh>
#include <SDL2pp/Point.hh>

#include "controller/game_controller.h"
#include "texture/texture_storage.h"

View::MenuRenderer::MenuRenderer(
    Weak<Controller::GameController> controller
) {
    auto controller_locked = controller.lock();
    window = controller_locked->get_window();
    renderer = controller_locked->get_renderer();
    texture_storage = controller_locked->get_texture_storage();
}

void View::MenuRenderer::render_menu() {
    SDL2pp::Color current_fill_color = renderer->GetDrawColor();
    renderer->SetDrawColor(55, 55, 55, 55);
    renderer->FillRect(
        60, 60,
        300, 300
    );
    renderer->SetDrawColor(current_fill_color);
}
