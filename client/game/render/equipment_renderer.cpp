#include "equipment_renderer.h"

#include <cstdint>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Rect.hh>

#include "asset/asset_manager.h"
#include "common/model/weapon.h"
#include "common/weapon_id.h"
#include "controller/game_controller.h"
#include "model/game_state.h"
#include "model/rendered_player.h"
#include "utils/enum_translator.h"
#include "utils/pane_scalator.h"
#include "utils/number_texture_generator.h"

void View::EquipmentRenderer::render_ammo(Shared<RenderedPlayer> player) {
    auto weapon = player->get_current_weapon();
    int loaded_ammo = weapon->get_loaded_ammo();
    int total_ammo = weapon->get_total_ammo();

    auto loaded_numbers = View::NumberTextureGenerator::get_hud_number(loaded_ammo);
    auto total_numbers = View::NumberTextureGenerator::get_hud_number(total_ammo);
    auto separator = View::NumberTextureGenerator::get_separator();

    for (auto& slice: loaded_numbers.first) {
        current_ammo.emplace_back(controller);
        current_ammo.front().set_texture(loaded_numbers.second);
        current_ammo.front().set_texture_slice(slice);
    }
    current_ammo.emplace_back(controller);
    current_ammo.front().set_texture(separator.second);
    current_ammo.front().set_texture_slice(separator.first);
    for (auto& slice: total_numbers.first) {
        current_ammo.emplace_back(controller);
        current_ammo.front().set_texture(total_numbers.second);
        current_ammo.front().set_texture_slice(slice);
    }
}

void View::EquipmentRenderer::render_weapon(Shared<View::RenderedPlayer> player) {
    auto weapon = player->get_current_weapon();
    Model::WeaponID weapon_id = weapon->get_weapon_id();
    if (weapon_id == Model::WeaponID::BOMB) return;
    auto weapon_texture = asset_manager->get_texture(
        Model::EnumTranslator::get_hud_texture_from_weapon(weapon_id)
    );
    current_weapon_slot.set_texture(weapon_texture);
    current_weapon_slot.set_size(weapon_texture->GetSize());
    View::PaneScalator::scalate_width_with_aspect_ratio(&current_weapon_slot, 15);

    current_ammo.clear();
    if (weapon_id != Model::WeaponID::KNIFE && weapon_id != Model::WeaponID::BOMB)
        render_ammo(player);
}

void View::EquipmentRenderer::render_bomb(Shared<RenderedPlayer> player) {
    auto weapon = player->get_current_weapon();
    Model::WeaponID weapon_id = weapon->get_weapon_id();
    if (weapon_id == Model::WeaponID::BOMB) return;

    auto bomb_texture = asset_manager->get_texture(
        Model::EnumTranslator::get_hud_texture_from_weapon(Model::WeaponID::BOMB)
    );
    bomb_slot.set_texture(bomb_texture);
    bomb_slot.set_size(bomb_texture->GetSize());
    View::PaneScalator::scalate_width_with_aspect_ratio(&bomb_slot, 15);
}

View::EquipmentRenderer::EquipmentRenderer(Weak<Controller::GameController> controller,
                                           View::VerticalPane& viewport):
        View::Renderer(controller),
        controller(controller),
        viewport(viewport),
        items(controller),
        bomb_slot(controller),
        current_weapon_data(controller),
        current_weapon_slot(controller) {
    items.set_vertical_alignment(1.0f);
    items.set_horizontal_alignment(0.0f);

    items.add_child(&bomb_slot);
    items.add_child(&current_weapon_data);
}

void View::EquipmentRenderer::render(const Model::GameState& game_state, uint8_t) {
    auto player = game_state.get_reference_player();
    if (!player) return;
    render_weapon(player);
}
