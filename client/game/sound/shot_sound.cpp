#include "shot_sound.h"

#include "asset/asset_manager.h"
#include "controller/game_controller.h"
#include "utils/enum_translator.h"

View::ShotSound::ShotSound(
    Weak<Controller::GameController> controller,
    short_id_t player_id,
    Model::WeaponID weapon_id
): View::SoundEffect(controller, player_id) {
    auto asset_manager = controller.lock()->get_asset_manager();
    chunk = asset_manager->get_sound(Model::EnumTranslator::get_sound_from_weapon(weapon_id));
}
