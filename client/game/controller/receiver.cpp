#include "receiver.h"

#include <exception>
#include <memory>
#include <utility>
#include <variant>

#include "client/net/client_protocol.h"
#include "common/DTO/dto_variant.h"
#include "common/overloaded.h"
#include "common/team.h"
#include "event/end_of_game_event.h"
#include "event/generate_map_event.h"
#include "event/update_game_state_event.h"
#include "event/update_player_id_event.h"
#include "event/update_role_event.h"

#include "game_controller.h"

void Controller::Receiver::update_game_state(DTO::GameStateDTO&& dto) {
    if (dto.ended) {
        keep_running = false;
        try {
            controller.lock()->push_event(make_shared<Model::EndOfGameEvent>());
        } catch (const std::exception&) {}
    } else {
        try {
            controller.lock()->push_event(make_shared<Model::UpdateGameStateEvent>(std::move(dto)));
        } catch (const std::exception&) {}
    }
}

void Controller::Receiver::update_player_id(DTO::PlayerIDDTO&& dto) {
    try {
        controller.lock()->push_event(make_shared<Model::UpdatePlayerIDEvent>(dto.id));
    } catch (const std::exception&) {}
}

void Controller::Receiver::update_current_team(DTO::TeamIDDTO&& dto) {
    try {
        controller.lock()->push_event(make_shared<Model::UpdateRoleEvent>((Model::TeamID)dto.id));
    } catch (const std::exception&) {}
}

void Controller::Receiver::generate_map(DTO::MapDTO&& dto) {
    try {
        controller.lock()->push_event(make_shared<Model::GenerateMapEvent>(std::move(dto)));
    } catch (const std::exception&) {}
}

void Controller::Receiver::receive_server_info() {
    auto variant = protocol->receive_variant();
    std::visit(overloaded{[this](DTO::GameStateDTO&& d) { update_game_state(std::move(d)); },
                          [this](DTO::PlayerIDDTO&& d) { update_player_id(std::move(d)); },
                          [this](DTO::TeamIDDTO&& d) { update_current_team(std::move(d)); },
                          [this](DTO::MapDTO&& d) { generate_map(std::move(d)); },
                          // TODO: Fix this
                          [](DTO::MapNameListDTO&&) {}, [](DTO::GameListDTO&&) {},
                          [](DTO::ConfigDTO&&) {}},
               std::move(variant));
}

Controller::Receiver::Receiver(Weak<GameController> controller,
                               Shared<Net::ClientProtocol> protocol):
        keep_running(true), controller(controller), protocol(protocol) {
    start();
}

void Controller::Receiver::run() {
    while (keep_running) {
        try {
            receive_server_info();
        } catch (const std::exception& e) {
            keep_running = false;
            try {
                controller.lock()->push_event(make_shared<Model::EndOfGameEvent>());
            } catch (const std::exception&) {}
        }
    }
}

Controller::Receiver::~Receiver() {
    keep_running = false;
    join();
}
