#ifndef CLIENT_GAME_RENDER_EQUIPMENT_RENDERER_H
#define CLIENT_GAME_RENDER_EQUIPMENT_RENDERER_H

#include <cstdint>

#include "entity/vertical_pane.h"
#include "entity/horizontal_pane.h"
#include "entity/pane.h"

#include "renderer.h"

namespace Controller {
class GameController;
};

namespace Model {
class GameState;
};

namespace View {
class RenderedPlayer;

class EquipmentRenderer: public Renderer {
private:
    Weak<Controller::GameController> controller;
    VerticalPane& viewport;
    VerticalPane items;
    Pane bomb_slot;
    HorizontalPane current_weapon_data;
    Pane current_weapon_slot;
    std::list<Pane> current_ammo;
    std::list<Pane> max_ammo;

    void render_ammo(Shared<RenderedPlayer> player);
    void render_weapon(Shared<RenderedPlayer> player);
    void render_bomb(Shared<RenderedPlayer> player);

public:
    EquipmentRenderer(Weak<Controller::GameController> controller, VerticalPane& viewport);

    void render(const Model::GameState& game_state, uint8_t) override;

    ~EquipmentRenderer() override = default;
};
};

#endif // CLIENT_GAME_RENDER_EQUIPMENT_RENDERER_H
