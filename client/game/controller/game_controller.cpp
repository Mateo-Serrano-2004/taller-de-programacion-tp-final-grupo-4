#include "game_controller.h"

#include <iostream>
#include <utility>
#include <atomic>

#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>

#include "common/DTO/game_state_dto.h"
#include "common/event_type.h"

#include "client/net/client_protocol.h"
#include "client/exception/closed_app.h"

#include "context/context_manager.h"
#include "handler/game_state_manager.h"
#include "asset/asset_manager.h"

Controller::GameController::GameController(
	Shared<SDL2pp::Window> window,
	Shared<SDL2pp::Renderer> renderer,
	Shared<Model::AssetManager> asset_manager,
	Shared<Context::ContextManager> context_manager,
	Shared<Net::ClientProtocol> protocol
): Controller::BaseController(window, renderer, asset_manager, context_manager),
   protocol(protocol),
   game_state_manager(
		make_shared<Controller::GameStateManager>(
			protocol->receive_player_id(),
			Weak<SDL2pp::Window>(window)
		)
   ) {
	sender = make_unique<Controller::Sender>(&sender_queue, protocol);
	receiver = make_unique<Controller::Receiver>(this, protocol);
}

void Controller::GameController::process_event(Shared<Model::Event> event) {
	auto event_type = event->get_type();
	if (event->get_type() == Model::EventType::WINDOW_RESIZE) {
		context_manager->propage_event(event);
    } else if (
        event_type == Model::EventType::SWITCH_CONTEXT
    ) {
        context_manager->propage_event(event);
    } else {
		try {
			sender_queue.push(event);
		} catch (const ClosedQueue&) {
			// Just wait, controller will end later
		}
	}

	if (event_type == Model::EventType::QUIT) {
		std::cout << "Received a QUIT event\n";
		// Sender will always terminate itself
		receiver.reset();
		throw ClosedAppException("Closed app"); 
	}
}

Shared<Controller::GameStateManager> Controller::GameController::get_game_state_manager() {
    return game_state_manager;
}
