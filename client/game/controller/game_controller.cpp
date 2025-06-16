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

#include "event/switch_context_event.h"
#include "event/quit_event.h"

Controller::GameController::GameController(
	Shared<SDL2pp::Window> window,
	Shared<SDL2pp::Renderer> renderer,
	Shared<Model::AssetManager> asset_manager,
	Shared<Context::ContextManager> context_manager,
	Shared<Net::ClientProtocol> protocol
): Controller::BaseController(window, renderer, asset_manager, context_manager),
   protocol(protocol) {
	sender = make_unique<Controller::Sender>(&sender_queue, protocol);
}

void Controller::GameController::process_event(Shared<Model::Event> event) {
	auto event_type = event->get_type();
	if (event_type == Model::EventType::SWITCH_CONTEXT) {
		auto switch_context_event = std::static_pointer_cast<Model::SwitchContextEvent>(event);
        context_manager->set_current_context(switch_context_event->get_new_context_name());
    } else if (event_type == Model::EventType::END_OF_GAME) {
		context_manager->set_current_context("end-of-game");
	} else {
		try {
			sender_queue.push(event);
		} catch (const ClosedQueue&) {}
	}

	if (event_type == Model::EventType::QUIT) {
		std::cout << "Received a QUIT event\n";
		receiver.reset();
		sender_queue.close();
		sender.reset();
		throw ClosedAppException("Closed app"); 
	}

	if (event_type == Model::EventType::END_OF_GAME) {
		std::cout << "Received a END_OF_GAME event\n";
	}
}

Shared<Controller::GameStateManager> Controller::GameController::get_game_state_manager() {
    return game_state_manager;
}

void Controller::GameController::build_game_state_manager(
	Weak<Controller::GameController> self,
	short_id_t player_id
) {
	game_state_manager = make_shared<Controller::GameStateManager>(self, player_id);
	receiver = make_unique<Controller::Receiver>(self, protocol);
}
