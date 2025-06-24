#include "shot_sound.h"

#include "asset/asset_manager.h"
#include "controller/game_controller.h"
#include "utils/enum_translator.h"

View::ShotSound::ShotSound(Weak<Controller::GameController> controller, Model::WeaponID weapon_id,
                           short_id_t player_id):
        View::TrackingSoundEffect(
                controller, Model::EnumTranslator::get_sound_from_weapon(weapon_id), player_id) {}
