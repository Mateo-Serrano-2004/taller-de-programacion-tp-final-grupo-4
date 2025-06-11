#ifndef CLIENT_GAME_RENDER_HUD_RENDERER_H
#define CLIENT_GAME_RENDER_HUD_RENDERER_H

#include <vector>

#include "common/definitions.h"

#include "renderer.h"

namespace SDL2pp {
class Texture;
};

namespace Controller {
class GameController;
class GameStateManager;
};

namespace View {
class RenderedPlayer;

class HUDRenderer: public Renderer {
protected:
    Shared<Controller::GameStateManager> game_state_manager;
    Shared<SDL2pp::Texture> hud_numbers;

    std::vector<uint8_t> get_units(uint16_t number);

    std::vector<uint8_t> get_units_of_time_left(uint16_t seconds_left);
    void render_number(uint8_t number, coord_t pos_x, coord_t pos_y);
    void render_time();
    void render_money(Shared<RenderedPlayer> player);
    // void render_equipment(Shared<View::RenderedPlayer> player);

public:
    HUDRenderer(Weak<Controller::GameController> controller);

    void render() override;

    ~HUDRenderer() override = default;
};
};

#endif // CLIENT_GAME_RENDER_HUD_RENDERER_H
