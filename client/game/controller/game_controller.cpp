#include "game_controller.h"

#include <iostream>
#include <utility>
#include <atomic>

#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>

#include "common/DTO/game_state_dto.h"

#include "client/net/client_protocol.h"
#include "client/exception/closed_app.h"

#include "context/context_manager.h"
#include "context/pick_role_context.h"

#include "handler/game_state_manager.h"

#include "asset/asset_manager.h"

#include "event/switch_context_event.h"
#include "event/quit_event.h"
#include "event/update_player_id_event.h"
#include "event/update_role_event.h"
#include "event/transfered_event.h"

Controller::GameController::GameController(
	Shared<SDL2pp::Window> window,
	Shared<SDL2pp::Renderer> renderer,
	Shared<Model::AssetManager> asset_manager,
	Shared<Context::ContextManager> context_manager,
	Shared<Net::ClientProtocol> protocol
): Controller::BaseController(window, renderer, asset_manager, context_manager),
   protocol(protocol) {
	sender = make_unique<Controller::Sender>(&sender_queue, protocol);
	bind_handlers();
}

void Controller::GameController::handle_switch_context(Shared<Model::Event> event) {
	auto switch_context_event = std::static_pointer_cast<Model::SwitchContextEvent>(event);
	context_manager->set_current_context(switch_context_event->get_new_context_name());
}

void Controller::GameController::handle_end_of_game(Shared<Model::Event>) {
	context_manager->set_current_context("end-of-game");
}

void Controller::GameController::handle_update_player_id(Shared<Model::Event> event) {
	auto update_player_id_event = std::static_pointer_cast<Model::UpdatePlayerIDEvent>(event);
	game_state_manager->update_player_id(update_player_id_event->get_new_id());
}

void Controller::GameController::handle_update_role(Shared<Model::Event> event) {
	auto update_role_event = std::static_pointer_cast<Model::UpdateRoleEvent>(event);
	auto pick_role_context = context_manager->get_context("pick-role");
	std::static_pointer_cast<Context::PickRoleContext>(pick_role_context)->update_team(
		update_role_event->get_team()
	);
}

bool Controller::GameController::try_handle(Shared<Model::Event> event) {
	auto handler = handlers.find(event->get_type());
	if (handler == handlers.end()) return false;
	handler->second(event);
	return true;
}

void Controller::GameController::bind_handlers() {
	handlers[Model::EventType::SWITCH_CONTEXT] = [this](Shared<Model::Event> event) {
		handle_switch_context(event);
	};
	handlers[Model::EventType::END_OF_GAME] = [this](Shared<Model::Event> event) {
		handle_end_of_game(event);
	};
	handlers[Model::EventType::UPDATE_PLAYER_ID] = [this](Shared<Model::Event> event) {
		handle_update_player_id(event);
	};
	handlers[Model::EventType::UPDATE_ROLE] = [this](Shared<Model::Event> event) {
		handle_update_role(event);
	};
}

void Controller::GameController::process_event(Shared<Model::Event> event) {
	auto event_type = event->get_type();
    if (!try_handle(event)) {
		if (event_type == Model::EventType::QUIT) receiver.reset();
		try {
			auto transfered_event = std::static_pointer_cast<Model::TransferedEvent>(event);
			sender_queue.push(transfered_event);
		} catch (const ClosedQueue&) {}
	}

	if (event_type == Model::EventType::QUIT) {
		std::cout << "Received a QUIT event\n";
		throw ClosedAppException("Closed app"); 
	}

	if (event_type == Model::EventType::END_OF_GAME) {
		std::cout << "Received a END_OF_GAME event\n";
	}
}

Shared<Controller::GameStateManager> Controller::GameController::get_game_state_manager() {
    return game_state_manager;
}

void Controller::GameController::set_self_pointer(Weak<Controller::GameController> self) {
	game_state_manager = make_shared<Controller::GameStateManager>(self);
	receiver = make_unique<Controller::Receiver>(self, protocol);
}
