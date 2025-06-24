#include <cstdint>
#include <thread>
#include <utility>
#include <variant>

#include "client/game/event/movement_event.h"
#include "client/net/client_protocol.h"
#include "common/socket.h"
#include "gtest/gtest.h"
#include "server/events/events.h"
#include "server/net/server_protocol.h"

TEST(MovementTest, send_and_receive_movement) {
    Socket server_socket("8080");

    std::thread client_thread([&]() {
        Socket client_socket("localhost", "8080");
        Net::ClientProtocol protocol(client_socket);
        Model::MovementEvent movement(1, -1);
        EXPECT_NO_THROW(protocol.send_event(movement.as_dto()));
    });

    Socket peer = server_socket.accept();
    ServerProtocol protocol(std::move(peer));
    auto received_event = protocol.receive_event();
    auto received_movement = std::get<MovementEvent>(std::get<GameEventVariant>(received_event));
    EXPECT_EQ(received_movement.get_direction().get_x(), 1);
    EXPECT_EQ(received_movement.get_direction().get_y(), -1);

    client_thread.join();
}
