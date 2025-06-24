#include "equipment_renderer.h"

#include <cstdint>

#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include "asset/asset_manager.h"
#include "common/model/weapon.h"
#include "common/weapon_id.h"
#include "controller/game_controller.h"
#include "model/game_state.h"
#include "model/rendered_player.h"
#include "utils/enum_translator.h"
#include "utils/number_texture_slicer.h"
#include "utils/pane_scalator.h"

void View::EquipmentRenderer::set_up_bomb() {
    auto bomb_texture = asset_manager->get_texture(
            Model::EnumTranslator::get_hud_texture_from_weapon(Model::WeaponID::BOMB));
    bomb_slot.set_texture(bomb_texture);
    bomb_slot.set_size(bomb_texture->GetSize());
    View::PaneScalator::scalate_height_with_aspect_ratio(&bomb_slot, 25);
}

void View::EquipmentRenderer::render_number(int ammo, std::list<View::Pane>& list) {
    auto slices = View::NumberTextureSlicer::get_hud_number(ammo);
    auto numbers_texture = asset_manager->get_texture(Model::TextureID::HUD_NUMS);

    for (auto& slice: slices) {
        list.emplace_back(controller);
        auto number = &list.back();
        number->set_texture(numbers_texture);
        number->set_texture_slice(slice);
        number->set_size(SDL2pp::Point(slice.GetW(), slice.GetH()));
        number->set_draw_texture(true);
        View::PaneScalator::scalate_height_with_aspect_ratio(number, 15);
    }
}

void View::EquipmentRenderer::render_separator() {
    auto slice = View::NumberTextureSlicer::get_separator();
    auto numbers_texture = asset_manager->get_texture(Model::TextureID::HUD_NUMS);

    separator.set_texture(numbers_texture);
    separator.set_texture_slice(slice);
    separator.set_draw_texture(true);
    separator.set_size(SDL2pp::Point(slice.GetW(), slice.GetH()));
    View::PaneScalator::scalate_height_with_aspect_ratio(&separator, 15);
}

void View::EquipmentRenderer::render_ammo(Shared<RenderedPlayer> player) {
    auto weapon = player->get_current_weapon();
    int loaded_ammo = weapon->get_loaded_ammo();
    int total_ammo = weapon->get_total_ammo();

    render_number(loaded_ammo, loaded_ammo_numbers);
    for (auto& number: loaded_ammo_numbers) {
        loaded_ammo_data.add_child(&number);
    }

    render_number(total_ammo, total_ammo_numbers);
    for (auto& number: total_ammo_numbers) {
        total_ammo_data.add_child(&number);
    }
}

void View::EquipmentRenderer::render_weapon(Shared<View::RenderedPlayer> player) {
    auto weapon = player->get_current_weapon();
    Model::WeaponID weapon_id = weapon->get_weapon_id();
    auto weapon_texture = asset_manager->get_texture(
            Model::EnumTranslator::get_hud_texture_from_weapon(weapon_id));
    current_weapon_slot.set_texture(weapon_texture);
    current_weapon_slot.set_size(weapon_texture->GetSize());
    current_weapon_slot.set_draw_texture(true);
    View::PaneScalator::scalate_height_with_aspect_ratio(&current_weapon_slot, 15);
    if (weapon_id == Model::WeaponID::BOMB)
        View::PaneScalator::scalate_height_with_aspect_ratio(&current_weapon_slot, 25);

    loaded_ammo_data.clear_children();
    total_ammo_data.clear_children();
    loaded_ammo_numbers.clear();
    total_ammo_numbers.clear();
    if (weapon_id != Model::WeaponID::KNIFE && weapon_id != Model::WeaponID::BOMB) {
        separator.set_draw_texture(true);
        render_ammo(player);
    } else {
        separator.set_draw_texture(false);
    }
}

void View::EquipmentRenderer::render_bomb(Shared<RenderedPlayer> player) {
    auto weapon = player->get_current_weapon();
    Model::WeaponID weapon_id = weapon->get_weapon_id();
    if (weapon_id == Model::WeaponID::BOMB)
        bomb_slot.set_draw_texture(false);
    else
        bomb_slot.set_draw_texture(true);
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
        ammo_data(controller),
        loaded_ammo_data(controller),
        separator(controller),
        total_ammo_data(controller) {
    viewport->add_child(&items);

    items.set_fit_to_children(true);
    items.set_vertical_alignment(1.0f);
    items.set_horizontal_alignment(0.0f);
    items.add_child(&bomb_slot);
    items.add_child(&current_weapon_data);

    current_weapon_data.set_fit_to_children(true);
    current_weapon_data.add_child(&current_weapon_slot);
    current_weapon_data.add_child(&ammo_data);

    render_separator();

    ammo_data.set_horizontal_alignment(0.0f);
    ammo_data.set_fit_to_children(true);
    ammo_data.set_gap_x(3);
    ammo_data.add_child(&loaded_ammo_data);
    ammo_data.add_child(&separator);
    ammo_data.add_child(&total_ammo_data);

    loaded_ammo_data.set_fit_to_children(true);
    total_ammo_data.set_fit_to_children(true);

    set_up_bomb();
}

void View::EquipmentRenderer::render(const Model::GameState& game_state, uint8_t) {
    items.set_position(SDL2pp::Point(0, viewport->get_height() - 60));
    auto player = game_state.get_reference_player();
    if (!player)
        return;
    render_weapon(player);
    if (player->get_has_bomb()) {
        render_bomb(player);
    }
}
