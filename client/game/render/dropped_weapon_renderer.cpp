#include "dropped_weapon_renderer.h"

#include <SDL2pp/Point.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL2pp.hh>

#include "asset/asset_manager.h"
#include "asset/texture_id.h"
#include "common/DTO/drop_weapon_dto.h"
#include "common/definitions.h"
#include "common/weapon_id.h"
#include "controller/game_controller.h"
#include "model/game_state.h"
#include "utils/enum_translator.h"

#include "camera.h"

View::DroppedWeaponRenderer::DroppedWeaponRenderer(Weak<Controller::GameController> controller):
        renderer(controller.lock()->get_renderer()),
        manager(controller.lock()->get_asset_manager()) {}

void View::DroppedWeaponRenderer::render_weapons(const Model::GameState& game_state) {
    auto camera = game_state.camera;
    for (auto& dweapon: game_state.dropped_weapons) {
        coord_t x = dweapon->position_x;
        coord_t y = dweapon->position_y;
        auto view = camera.get_camera_view(SDL2pp::Point(x, y));
        auto texture_id = Model::EnumTranslator::get_dropped_from_weapon(dweapon->weapon_id);
        renderer->Copy(*(manager->get_texture(texture_id)), SDL2pp::NullOpt, view);
    }
}
