#include "game_controller.h"

#include <utility>

#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>

#include "common/DTO/game_state_dto.h"
#include "common/event_type.h"

#include "handler/game_state_manager.h"
#include "texture/texture_storage.h"
#include "context/context_manager.h"

#include "client/net/client_protocol.h"

void Controller::GameController::process_event(Shared<Model::Event> event) {
	sender_queue.push(std::move(event));
}

Controller::GameController::GameController(
	Shared<SDL2pp::Window> window,
	Shared<SDL2pp::Renderer> renderer,
	Shared<Model::TextureStorage> texture_storage,
	Shared<Context::ContextManager> context_manager,
	Net::ClientProtocol* protocol
): Controller::BaseController(window, renderer, texture_storage, context_manager),
   protocol(protocol),
   game_state_manager(make_shared<Controller::GameStateManager>(
	protocol->receive_player_id(),
	Weak<SDL2pp::Window>(window)
   )),
   sender(&sender_queue, protocol),
   receiver(this, protocol) {}

Shared<Controller::GameStateManager> Controller::GameController::get_game_state_manager() {
    return game_state_manager;
}
