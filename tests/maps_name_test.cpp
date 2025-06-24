#include <cstdint>
#include <thread>
#include <utility>

#include "client/net/client_protocol.h"
#include "common/DTO/dto_variant.h"
#include "common/socket.h"
#include "gtest/gtest.h"
#include "server/net/server_protocol.h"

TEST(MapsNameTest, send_and_receive_maps_name) {
    Socket server_socket("8080");

    std::string map_name1 = "de_dust";
    std::string map_name2 = "de_mirage";
    std::string map_name3 = "de_rio";

    DTO::MapNameListDTO map_name_list({map_name1, map_name2, map_name3});

    std::thread client_thread([&]() {
        Socket client_socket("localhost", "8080");
        Net::ClientProtocol protocol(client_socket);
        DTO::MapNameListDTO received_map_name_list =
                std::get<DTO::MapNameListDTO>(protocol.receive_variant());

        EXPECT_EQ(received_map_name_list.maps_names.size(), 3);

        EXPECT_EQ(received_map_name_list.maps_names[0], "de_dust");
        EXPECT_EQ(received_map_name_list.maps_names[1], "de_mirage");
        EXPECT_EQ(received_map_name_list.maps_names[2], "de_rio");
    });

    Socket peer = server_socket.accept();
    ServerProtocol protocol(std::move(peer));
    EXPECT_NO_THROW(protocol.send_variant(DTO::DTOVariant(map_name_list)));

    client_thread.join();
}
