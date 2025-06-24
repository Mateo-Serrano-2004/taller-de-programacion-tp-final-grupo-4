#include <cstdint>
#include <thread>
#include <utility>

#include "client/net/client_protocol.h"
#include "common/DTO/dto_variant.h"
#include "common/model/vector_2d.h"
#include "common/socket.h"
#include "gtest/gtest.h"
#include "server/net/server_protocol.h"

TEST(GameStateTest, send_and_receive_game_state) {
    Socket server_socket("8080");

    DTO::WeaponDTO weapon1(Model::WeaponID::M3, 30, 150);
    DTO::WeaponDTO weapon2(Model::WeaponID::AK47, 15, 70);
    DTO::PlayerDTO player1(1, 1, 30, 1500, 2, 40, "Juan", weapon1, 0, 0, 1, 100, 1, 0, 0, 0, 1, 1);
    DTO::PlayerDTO player2(3, 2, 60, 6000, 4, 26, "Maria", weapon2, 1, 1, 0, 70, 2, 0, 0, 0, 0, 0);

    std::vector<DTO::DropWeaponDTO> dropped_weapons = {
            DTO::DropWeaponDTO(Model::WeaponID::M3, 2, 40)};
    DTO::RoundDTO round(RoundState::Buying, false, 25, Model::TeamID::NONE, false, false,
                        Physics::Vector2D(0, 0), 0, dropped_weapons);

    DTO::GameStateDTO game_state(GameState::Playing, {player1, player2}, false, Model::TeamID::NONE,
                                 round, 1, 3);

    std::thread client_thread([&]() {
        Socket client_socket("localhost", "8080");
        Net::ClientProtocol protocol(client_socket);
        DTO::GameStateDTO received_game_state =
                std::get<DTO::GameStateDTO>(protocol.receive_variant());

        EXPECT_EQ(received_game_state.game_state, GameState::Playing);
        EXPECT_EQ(received_game_state.players.size(), 2);

        EXPECT_EQ(received_game_state.players[0].player_id, 1);
        EXPECT_EQ(received_game_state.players[0].role_id, 1);
        EXPECT_EQ(received_game_state.players[0].angle, 30);
        EXPECT_EQ(received_game_state.players[0].money, 1500);
        EXPECT_EQ(received_game_state.players[0].position_x, 2);
        EXPECT_EQ(received_game_state.players[0].position_y, 40);
        EXPECT_EQ(received_game_state.players[0].name, "Juan");
        EXPECT_EQ(received_game_state.players[0].weapon_dto.weapon_id, Model::WeaponID::M3);
        EXPECT_EQ(received_game_state.players[0].weapon_dto.loaded_ammo, 30);
        EXPECT_EQ(received_game_state.players[0].weapon_dto.total_ammo, 150);
        EXPECT_EQ(received_game_state.players[0].shooting, 0);
        EXPECT_EQ(received_game_state.players[0].defusing_bomb, 0);
        EXPECT_EQ(received_game_state.players[0].reloading, 1);
        EXPECT_EQ(received_game_state.players[0].health, 100);
        EXPECT_EQ(received_game_state.players[0].team, 1);
        EXPECT_EQ(received_game_state.players[0].kills, 0);
        EXPECT_EQ(received_game_state.players[0].deaths, 0);
        EXPECT_EQ(received_game_state.players[0].planting_progress, 0);
        EXPECT_EQ(received_game_state.players[0].has_hit, 1);

        EXPECT_EQ(received_game_state.players[1].player_id, 3);
        EXPECT_EQ(received_game_state.players[1].role_id, 2);
        EXPECT_EQ(received_game_state.players[1].angle, 60);
        EXPECT_EQ(received_game_state.players[1].money, 6000);
        EXPECT_EQ(received_game_state.players[1].position_x, 4);
        EXPECT_EQ(received_game_state.players[1].position_y, 26);
        EXPECT_EQ(received_game_state.players[1].name, "Maria");
        EXPECT_EQ(received_game_state.players[1].weapon_dto.weapon_id, Model::WeaponID::AK47);
        EXPECT_EQ(received_game_state.players[1].weapon_dto.loaded_ammo, 15);
        EXPECT_EQ(received_game_state.players[1].weapon_dto.total_ammo, 70);
        EXPECT_EQ(received_game_state.players[1].shooting, 1);
        EXPECT_EQ(received_game_state.players[1].defusing_bomb, 1);
        EXPECT_EQ(received_game_state.players[1].reloading, 0);
        EXPECT_EQ(received_game_state.players[1].health, 70);
        EXPECT_EQ(received_game_state.players[1].team, 2);
        EXPECT_EQ(received_game_state.players[1].kills, 0);
        EXPECT_EQ(received_game_state.players[1].deaths, 0);
        EXPECT_EQ(received_game_state.players[1].planting_progress, 0);
        EXPECT_EQ(received_game_state.players[1].has_hit, 0);

        EXPECT_EQ(received_game_state.round.state, RoundState::Buying);
        EXPECT_EQ(received_game_state.round.ended, false);
        EXPECT_EQ(received_game_state.round.time_left, 25);
        EXPECT_EQ(received_game_state.round.winner, Model::TeamID::NONE);
        EXPECT_EQ(received_game_state.round.bomb_planted, false);
        EXPECT_EQ(received_game_state.round.bomb_defused, false);
        EXPECT_EQ(received_game_state.round.bomb_position.get_x(), 0);
        EXPECT_EQ(received_game_state.round.bomb_position.get_y(), 0);
        EXPECT_EQ(received_game_state.round.defusing_progress, 0);
        EXPECT_EQ(received_game_state.round.dropped_weapons.size(), 1);
        EXPECT_EQ(received_game_state.round.dropped_weapons[0].weapon_id, Model::WeaponID::M3);
        EXPECT_EQ(received_game_state.round.dropped_weapons[0].position_x, 2);
        EXPECT_EQ(received_game_state.round.dropped_weapons[0].position_y, 40);

        EXPECT_EQ(received_game_state.ct_rounds_won, 1);
        EXPECT_EQ(received_game_state.tt_rounds_won, 3);
    });

    Socket peer = server_socket.accept();
    ServerProtocol protocol(std::move(peer));
    EXPECT_NO_THROW(protocol.send_variant(DTO::DTOVariant(game_state)));

    client_thread.join();
}
