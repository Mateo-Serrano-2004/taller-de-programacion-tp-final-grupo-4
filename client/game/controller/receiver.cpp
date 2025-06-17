#include "receiver.h"

#include <iostream>
#include <exception>
#include <variant>
#include <utility>

#include "common/overloaded.h"
#include "common/team.h"
#include "common/DTO/dto_variant.h"

#include "client/net/client_protocol.h"

#include "game_controller.h"

#include "handler/game_state_manager.h"

#include "event/end_of_game_event.h"
#include "event/update_player_id_event.h"
#include "event/update_role_event.h"

void Controller::Receiver::update_game_state(DTO::GameStateDTO&& dto) {
    if (dto.ended) {
        keep_running = false;
        try {
            controller.lock()->push_event(make_shared<Model::EndOfGameEvent>());
        } catch (const std::exception&) {}
    } else if (game_state_manager) {
        game_state_manager->update(std::move(dto));
    }
}

void Controller::Receiver::update_player_id(DTO::PlayerIDDTO&& dto) {
    try {
        controller.lock()->push_event(make_shared<Model::UpdatePlayerIDEvent>(dto.id));
    } catch (const std::exception&) {}
}

void Controller::Receiver::update_current_team(DTO::TeamIDDTO&& dto) {
    try {
        controller.lock()->push_event(make_shared<Model::UpdateRoleEvent>(
            (Model::TeamID) dto.id)
        );
    } catch (const std::exception&) {}
}

void Controller::Receiver::receive_server_info() {
    auto variant = protocol->receive_variant();
    std::visit(
        overloaded {
            [this](DTO::GameStateDTO&& d) { update_game_state(std::move(d)); },
            [this](DTO::PlayerIDDTO&& d) { update_player_id(std::move(d)); },
            [this](DTO::TeamIDDTO&& d) { update_current_team(std::move(d)); },
            // TODO: Fix this
            [](DTO::MapDTO&&) {},
            [](DTO::MapNameListDTO&&) {},
            [](DTO::GameListDTO&&) {}
        },
        std::move(variant)
    );
}

Controller::Receiver::Receiver(Weak<GameController> controller,
                               Shared<Net::ClientProtocol> protocol):
        keep_running(true),
        controller(controller),
        game_state_manager(controller.lock()->get_game_state_manager()),
        protocol(protocol) {
    start();
}

void Controller::Receiver::run() {
    while (keep_running) {
        try {
            receive_server_info();
        } catch (const std::exception& e) {
            std::cerr << "Receiver error: " << e.what() << "\n";
            keep_running = false;
        }
    }
    std::cout << "Finishing receiver\n";
}

Controller::Receiver::~Receiver() {
    keep_running = false;
    join();

    std::cout << "RECEIVER DESTROYED\n";
}
