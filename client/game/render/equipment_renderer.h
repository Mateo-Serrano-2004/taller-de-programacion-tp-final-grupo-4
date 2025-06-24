#ifndef CLIENT_GAME_RENDER_EQUIPMENT_RENDERER_H
#define CLIENT_GAME_RENDER_EQUIPMENT_RENDERER_H

#include <cstdint>
#include <list>

#include "entity/horizontal_pane.h"
#include "entity/pane.h"
#include "entity/vertical_pane.h"

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
    Pane* viewport;
    VerticalPane items;
    Pane bomb_slot;
    HorizontalPane current_weapon_data;
    Pane current_weapon_slot;
    HorizontalPane ammo_data;
    HorizontalPane loaded_ammo_data;
    std::list<Pane> loaded_ammo_numbers;
    Pane separator;
    HorizontalPane total_ammo_data;
    std::list<Pane> total_ammo_numbers;

    void set_up_bomb();

    void render_number(int ammo, std::list<Pane>& list);
    void render_separator();
    void render_ammo(Shared<RenderedPlayer> player);
    void render_weapon(Shared<RenderedPlayer> player);
    void render_bomb(Shared<RenderedPlayer> player);

public:
    EquipmentRenderer(Weak<Controller::GameController> controller, Pane* viewport);

    void render(const Model::GameState& game_state, uint8_t) override;

    ~EquipmentRenderer() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_RENDER_EQUIPMENT_RENDERER_H
