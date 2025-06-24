#include "game_controller.h"

#include <atomic>
#include <memory>
#include <utility>

#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Window.hh>

#include "asset/asset_loader.h"
#include "asset/asset_manager.h"
#include "client/exception/closed_app.h"
#include "client/exception/closed_game.h"
#include "client/net/client_protocol.h"
#include "common/DTO/game_state_dto.h"
#include "context/context_manager.h"
#include "context/pick_role_context.h"
#include "event/generate_map_event.h"
#include "event/quit_event.h"
#include "event/switch_context_event.h"
#include "event/transfered_event.h"
#include "event/update_game_state_event.h"
#include "event/update_player_id_event.h"
#include "event/update_role_event.h"
#include "handler/game_state_manager.h"

Controller::GameController::GameController(Shared<SDL2pp::Window> window,
                                           Shared<SDL2pp::Renderer> renderer,
                                           Shared<Model::AssetManager> asset_manager,
                                           Shared<Model::AssetLoader> asset_loader,
                                           Shared<Context::ContextManager> context_manager,
                                           Shared<Net::ClientProtocol> protocol):
        Controller::BaseController(window, renderer, asset_manager, asset_loader, context_manager),
        protocol(protocol) {
    sender = make_unique<Controller::Sender>(&sender_queue, protocol);
    bind_handlers();
}

void Controller::GameController::handle_switch_context(Shared<Model::Event> event) {
    auto switch_context_event = std::static_pointer_cast<Model::SwitchContextEvent>(event);
    context_manager->notify_event(switch_context_event);
    context_manager->set_current_context(switch_context_event->get_new_context_name());
}

void Controller::GameController::handle_end_of_game(Shared<Model::Event>) {
    sender_queue.close();
    sender.reset();
    receiver.reset();
    throw ClosedGameException("Closed game");
}

void Controller::GameController::handle_update_player_id(Shared<Model::Event> event) {
    auto update_player_id_event = std::static_pointer_cast<Model::UpdatePlayerIDEvent>(event);
    game_state_manager->update_player_id(update_player_id_event->get_new_id());
}

void Controller::GameController::handle_update_role(Shared<Model::Event> event) {
    auto update_role_event = std::static_pointer_cast<Model::UpdateRoleEvent>(event);
    auto pick_role_context = context_manager->get_context("pick-role");
    std::static_pointer_cast<Context::PickRoleContext>(pick_role_context)
            ->update_team(update_role_event->get_team());
}

void Controller::GameController::handle_generate_map(Shared<Model::Event> event) {
    auto generate_map_event = std::static_pointer_cast<Model::GenerateMapEvent>(event);
    auto new_map = asset_manager->generate_map(generate_map_event->get_map_dto());
    game_state_manager->update_map(new_map);
    context_manager->set_current_context("pick-role");
}

void Controller::GameController::handle_update_game_state(Shared<Model::Event> event) {
    auto update_game_state_event = std::static_pointer_cast<Model::UpdateGameStateEvent>(event);
    game_state_manager->update(update_game_state_event->get_dto());
}

bool Controller::GameController::try_handle(Shared<Model::Event> event) {
    auto handler = handlers.find(event->get_type());
    if (handler == handlers.end())
        return false;
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
    handlers[Model::EventType::GENERATE_MAP] = [this](Shared<Model::Event> event) {
        handle_generate_map(event);
    };
    handlers[Model::EventType::UPDATE_GAME_STATE] = [this](Shared<Model::Event> event) {
        handle_update_game_state(event);
    };
}

void Controller::GameController::process_event(Shared<Model::Event> event) {
    auto event_type = event->get_type();
    if (!try_handle(event)) {
        if (event_type == Model::EventType::QUIT || event_type == Model::EventType::LEAVE_GAME)
            receiver.reset();
        try {
            auto transfered_event = std::static_pointer_cast<Model::TransferedEvent>(event);
            sender_queue.push(transfered_event);
        } catch (const ClosedQueue&) {}
    }

    if (event_type == Model::EventType::QUIT) {
        throw ClosedAppException("Closed app");
    } else if (event_type == Model::EventType::LEAVE_GAME) {
        throw ClosedGameException("Closed game");
    }
}

Shared<Controller::GameStateManager> Controller::GameController::get_game_state_manager() {
    return game_state_manager;
}

void Controller::GameController::set_self_pointer(Weak<Controller::GameController> self) {
    game_state_manager = make_shared<Controller::GameStateManager>(self);
    receiver = make_unique<Controller::Receiver>(self, protocol);
}
