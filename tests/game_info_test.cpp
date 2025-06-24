#include <cstdint>
#include <thread>
#include <utility>

#include "client/net/client_protocol.h"
#include "common/DTO/dto_variant.h"
#include "common/socket.h"
#include "gtest/gtest.h"
#include "server/net/server_protocol.h"

TEST(GameInfoTest, send_and_receive_game_info) {
    Socket server_socket("8080");

    DTO::GameInfoDTO game_info(1, "Partida de Juan", 2, "de_dust");
    DTO::GameInfoDTO game_info2(2, "Partida de Maria", 3, "de_mirage");
    DTO::GameInfoDTO game_info3(3, "Brasil vs Argentina", 2, "de_rio");

    DTO::GameListDTO game_list({game_info, game_info2, game_info3});

    std::thread client_thread([&]() {
        Socket client_socket("localhost", "8080");
        Net::ClientProtocol protocol(client_socket);
        DTO::GameListDTO received_game_list =
                std::get<DTO::GameListDTO>(protocol.receive_variant());

        EXPECT_EQ(received_game_list.games.size(), 3);

        EXPECT_EQ(received_game_list.games[0].id, 1);
        EXPECT_EQ(received_game_list.games[0].name, "Partida de Juan");
        EXPECT_EQ(received_game_list.games[0].current_players, 2);
        EXPECT_EQ(received_game_list.games[0].map_name, "de_dust");

        EXPECT_EQ(received_game_list.games[1].id, 2);
        EXPECT_EQ(received_game_list.games[1].name, "Partida de Maria");
        EXPECT_EQ(received_game_list.games[1].current_players, 3);
        EXPECT_EQ(received_game_list.games[1].map_name, "de_mirage");

        EXPECT_EQ(received_game_list.games[2].id, 3);
        EXPECT_EQ(received_game_list.games[2].name, "Brasil vs Argentina");
        EXPECT_EQ(received_game_list.games[2].current_players, 2);
        EXPECT_EQ(received_game_list.games[2].map_name, "de_rio");
    });

    Socket peer = server_socket.accept();
    ServerProtocol protocol(std::move(peer));
    EXPECT_NO_THROW(protocol.send_variant(DTO::DTOVariant(game_list)));

    client_thread.join();
}
