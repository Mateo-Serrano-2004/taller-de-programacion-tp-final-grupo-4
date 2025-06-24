#include <cstdint>
#include <thread>
#include <utility>
#include <variant>

#include "client/game/event/create_game_event.h"
#include "client/net/client_protocol.h"
#include "common/socket.h"
#include "gtest/gtest.h"
#include "server/events/events.h"
#include "server/net/server_protocol.h"

TEST(CreateGameTest, send_and_receive_create_game) {
    Socket server_socket("8080");

    std::thread client_thread([&]() {
        Socket client_socket("localhost", "8080");
        Net::ClientProtocol protocol(client_socket);
        Model::CreateGameEvent create_game("Partida de Juan", "de_dust");
        EXPECT_NO_THROW(protocol.send_event(create_game.as_dto()));
    });

    Socket peer = server_socket.accept();
    ServerProtocol protocol(std::move(peer));
    auto received_event = protocol.receive_event();
    auto received_create_game = std::get<CreateGameEvent>(received_event);
    EXPECT_EQ(received_create_game.get_party_name(), "Partida de Juan");
    EXPECT_EQ(received_create_game.get_map_name(), "de_dust");
    client_thread.join();
}
