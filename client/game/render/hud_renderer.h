#ifndef CLIENT_GAME_RENDER_HUD_RENDERER_H
#define CLIENT_GAME_RENDER_HUD_RENDERER_H

#include <cstdint>
#include <list>
#include <vector>

#include <SDL2pp/Rect.hh>

#include "common/definitions.h"
#include "entity/horizontal_pane.h"
#include "entity/pane.h"

#include "equipment_renderer.h"
#include "renderer.h"

namespace SDL2pp {
class Texture;
};

namespace Controller {
class GameController;
class GameStateManager;
};  // namespace Controller

namespace View {
class RenderedPlayer;

class HUDRenderer: public Renderer {
protected:
    Weak<Controller::GameController> controller;
    Shared<Controller::GameStateManager> game_state_manager;
    Shared<SDL2pp::Texture> hud_numbers;
    Shared<SDL2pp::Texture> hud_symbols;

    VerticalPane viewport;
    Pane equipment_space;
    EquipmentRenderer equipment_renderer;
    HorizontalPane time;
    HorizontalPane stats;
    HorizontalPane health;
    HorizontalPane money;
    std::list<Pane> time_numbers;
    std::list<Pane> health_numbers;
    std::list<Pane> money_numbers;

    std::vector<SDL2pp::Rect> get_time_slices(int seconds_left);

    void render_item(std::list<View::Pane>& numbers, View::HorizontalPane& parent,
                     const SDL2pp::Rect& slice, Shared<SDL2pp::Texture> texture);

    void render_time(uint16_t time_left);
    void render_life_points(Shared<RenderedPlayer> player);
    void render_money(Shared<RenderedPlayer> player);

public:
    explicit HUDRenderer(Weak<Controller::GameController> controller);

    void render(const Model::GameState& game_state, uint8_t frames) override;

    ~HUDRenderer() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_RENDER_HUD_RENDERER_H
