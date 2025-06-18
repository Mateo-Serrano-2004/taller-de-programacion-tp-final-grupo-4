#include "animation.h"

#include <SDL2pp/Texture.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>

#include "controller/game_controller.h"

#include "handler/game_state_manager.h"

#include "asset/asset_manager.h"

View::Animation::Animation(
    Weak<Controller::GameController> controller,
    Model::AnimationID id
): View::Rendered(controller),
   Controller::AnimationIterator(controller.lock()->get_asset_manager()->get_animation(id)),
   frames_to_process(1),
   game_state_manager(controller.lock()->get_game_state_manager()) {}

void View::Animation::set_frames_to_process(uint8_t frames) {
    frames_to_process = frames;
}
