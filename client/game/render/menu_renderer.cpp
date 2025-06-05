#include "menu_renderer.h"

#include <algorithm>

#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Color.hh>
#include <SDL2pp/Point.hh>

#include "controller/game_controller.h"
#include "asset/asset_manager.h"

#include "entity/rendered.h"

View::MenuRenderer::MenuRenderer(
    Weak<Controller::GameController> controller
): View::Renderer(controller) {}

void View::MenuRenderer::add_to_render(Shared<Rendered> rendered) {
    rendereds.push_back(rendered);
}

void View::MenuRenderer::render() {
    std::for_each(
        rendereds.begin(),
        rendereds.end(),
        [] (Shared<Rendered>& rendered) {
            rendered->render();
        }
    );

    // SDL2pp::Color current_fill_color = renderer->GetDrawColor();
    // renderer->SetDrawColor(55, 55, 55, 255);
    // renderer->FillRect(
    //     60, 60,
    //     300, 300
    // );
    // renderer->SetDrawColor(current_fill_color);
}
