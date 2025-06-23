#include "reload_sound.h"

#include "asset/asset_manager.h"
#include "asset/sound_id.h"
#include "controller/game_controller.h"

View::ReloadSound::ReloadSound(
    Weak<Controller::GameController> controller,
    short_id_t player_id
): View::SoundEffect(controller, player_id) {
    auto asset_manager = controller.lock()->get_asset_manager();
    chunk = asset_manager->get_sound(Model::SoundID::RELOAD_SOUND);
}