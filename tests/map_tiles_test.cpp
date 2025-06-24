#include <cstdint>
#include <thread>
#include <utility>

#include "client/net/client_protocol.h"
#include "common/DTO/dto_variant.h"
#include "common/socket.h"
#include "gtest/gtest.h"
#include "server/net/server_protocol.h"

TEST(MapTilesTest, send_and_receive_map_tiles) {
    Socket server_socket("8080");

    PathMap map_tiles = {{"Walls/sand_wall.png", "Boxes/box.png", "Boxes/box.png"},
                         {"Walls/sand_wall.png", "Walls/sand_wall.png", ""},
                         {"Boxes/box.png", "Backgrounds/water.png", "Backgrounds/water.png"}};

    DTO::MapDTO map_tiles_dto(map_tiles);

    std::thread client_thread([&]() {
        Socket client_socket("localhost", "8080");
        Net::ClientProtocol protocol(client_socket);
        DTO::MapDTO received_map_tiles = std::get<DTO::MapDTO>(protocol.receive_variant());

        EXPECT_EQ(received_map_tiles.count_of_columns, 3);
        EXPECT_EQ(received_map_tiles.count_of_rows, 3);

        EXPECT_EQ(received_map_tiles.map[0][0], "Walls/sand_wall.png");
        EXPECT_EQ(received_map_tiles.map[0][1], "Boxes/box.png");
        EXPECT_EQ(received_map_tiles.map[0][2], "Boxes/box.png");

        EXPECT_EQ(received_map_tiles.map[1][0], "Walls/sand_wall.png");
        EXPECT_EQ(received_map_tiles.map[1][1], "Walls/sand_wall.png");
        EXPECT_EQ(received_map_tiles.map[1][2], "");

        EXPECT_EQ(received_map_tiles.map[2][0], "Boxes/box.png");
        EXPECT_EQ(received_map_tiles.map[2][1], "Backgrounds/water.png");
        EXPECT_EQ(received_map_tiles.map[2][2], "Backgrounds/water.png");
    });

    Socket peer = server_socket.accept();
    ServerProtocol protocol(std::move(peer));
    EXPECT_NO_THROW(protocol.send_variant(DTO::DTOVariant(map_tiles_dto)));

    client_thread.join();
}
