#include "animation.h"

#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include "asset/asset_manager.h"
#include "controller/base_controller.h"
#include "handler/game_state_manager.h"

View::Animation::Animation(Weak<Controller::BaseController> controller, int total_frames):
	View::Rendered(controller),
	current_frame(0),
	ended(false),
	total_frames(total_frames) {}

void View::Animation::step(int frames) {
	if (has_ended()) return;
	render();
	current_frame += frames;
	ended = (current_frame > total_frames);
}

bool View::Animation::has_ended() const {
	return ended;
}

void View::Animation::end() {
	ended = true;
}
