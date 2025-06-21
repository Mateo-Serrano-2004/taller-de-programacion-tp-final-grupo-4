#include "equipment_renderer.h"

#include <cstdint>
#include <iostream>
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
#include "utils/number_texture_slicer.h"

void View::EquipmentRenderer::render_number(int ammo) {
    auto slices = View::NumberTextureSlicer::get_hud_number(ammo);
    auto numbers_texture = asset_manager->get_texture(Model::TextureID::HUD_NUMS);

    for (auto& slice: slices) {
        numbers.emplace_back(controller);
        auto number = &numbers.front();
        number->set_texture(numbers_texture);
        number->set_texture_slice(slice);
        number->set_size(SDL2pp::Point(slice.GetW(), slice.GetH()));
        number->set_draw_texture(true);
        View::PaneScalator::scalate_width_with_aspect_ratio(number, 15);
    }
}

void View::EquipmentRenderer::render_separator() {
    auto slice = View::NumberTextureSlicer::get_separator();
    auto numbers_texture = asset_manager->get_texture(Model::TextureID::HUD_NUMS);

    numbers.emplace_back(controller);
    auto separator_sprite = &numbers.front();
    separator_sprite->set_texture(numbers_texture);
    separator_sprite->set_texture_slice(slice);
    separator_sprite->set_draw_texture(true);
    separator_sprite->set_size(SDL2pp::Point(slice.GetW(), slice.GetH()));
    View::PaneScalator::scalate_width_with_aspect_ratio(separator_sprite, 15);
}

void View::EquipmentRenderer::render_ammo(Shared<RenderedPlayer> player) {
    auto weapon = player->get_current_weapon();
    int loaded_ammo = weapon->get_loaded_ammo();
    int total_ammo = weapon->get_total_ammo();

    render_number(loaded_ammo);
    render_separator();
    render_number(total_ammo);

    ammo_data.set_width(0);
    for (auto& pane: numbers) {
        ammo_data.add_child(&pane);
        ammo_data.set_width(ammo_data.get_width() + pane.get_width());
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
    current_weapon_slot.set_draw_texture(true);
    View::PaneScalator::scalate_width_with_aspect_ratio(&current_weapon_slot, 15);

    ammo_data.clear_children();
    numbers.clear();
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
                                           View::Pane* viewport):
        View::Renderer(controller),
        controller(controller),
        viewport(viewport),
        items(controller),
        bomb_slot(controller),
        current_weapon_data(controller),
        current_weapon_slot(controller),
        ammo_data(controller) {
    viewport->add_child(&items);

    items.set_vertical_alignment(1.0f);
    items.set_horizontal_alignment(0.0f);
    items.add_child(&bomb_slot);
    items.add_child(&current_weapon_data);

    current_weapon_data.add_child(&current_weapon_slot);
    current_weapon_data.add_child(&ammo_data);

    ammo_data.set_height(15);
    ammo_data.set_horizontal_alignment(0.0f);
}

void View::EquipmentRenderer::render(const Model::GameState& game_state, uint8_t) {
    auto player = game_state.get_reference_player();
    if (!player) return;
    render_weapon(player);
}
