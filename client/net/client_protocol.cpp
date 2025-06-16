#include "client_protocol.h"

#include <vector>
#include <cstdint>
#include <arpa/inet.h>

#include "common/DTO/event_dto.h"

void Net::ClientProtocol::receive_weapon(DTO::WeaponDTO& weapon) {
    skt.recvall(&weapon.weapon_id, sizeof(weapon.weapon_id));
    skt.recvall(&weapon.loaded_ammo, sizeof(weapon.loaded_ammo));
    skt.recvall(&weapon.total_ammo, sizeof(weapon.total_ammo));

    weapon.total_ammo = ntohs(weapon.total_ammo);
}

void Net::ClientProtocol::receive_player(DTO::PlayerDTO& player) {
    uint8_t name_size = 0;

    skt.recvall(&player.player_id, sizeof(player.player_id));
    skt.recvall(&player.role_id, sizeof(player.role_id));
    skt.recvall(&player.shooting, sizeof(player.shooting));
    skt.recvall(&player.health, sizeof(player.health));
    skt.recvall(&player.team, sizeof(player.team));

    skt.recvall(&player.angle, sizeof(player.angle));
    player.angle = ntohs(player.angle);

    skt.recvall(&player.money, sizeof(player.money));
    player.money = ntohs(player.money);

    skt.recvall(&player.position_x, sizeof(player.position_x));
    player.position_x = ntohs(player.position_x);

    skt.recvall(&player.position_y, sizeof(player.position_y));
    player.position_y = ntohs(player.position_y);

    skt.recvall(&name_size, sizeof(name_size));
    player.name.resize(name_size);
    skt.recvall(player.name.data(), name_size);

    receive_weapon(player.weapon_dto);
}

void Net::ClientProtocol::receive_player_list(std::vector<DTO::PlayerDTO>& players) {
    uint8_t players_size;
    skt.recvall(&players_size, sizeof(players_size));

    for (uint8_t i = 0; i < players_size; i++) {
        DTO::PlayerDTO player;
        receive_player(player);
        players.push_back(player);
    }
}

DTO::RoundDTO Net::ClientProtocol::receive_round(DTO::RoundDTO& round) {
    skt.recvall(&round.state, sizeof(round.state));
    skt.recvall(&round.ended, sizeof(round.ended));
    skt.recvall(&round.time_left, sizeof(round.time_left));
    skt.recvall(&round.winner, sizeof(round.winner));

    round.time_left = htons(round.time_left);

    return round;
}

DTO::GameStateDTO Net::ClientProtocol::receive_match_state() {
    DTO::GameStateDTO game_state_dto;

    skt.recvall(&game_state_dto.game_state, sizeof(game_state_dto.game_state));
    skt.recvall(&game_state_dto.ended, sizeof(game_state_dto.ended));
    skt.recvall(&game_state_dto.winner, sizeof(game_state_dto.winner));
    skt.recvall(&game_state_dto.ct_rounds_won, sizeof(game_state_dto.ct_rounds_won));
    skt.recvall(&game_state_dto.tt_rounds_won, sizeof(game_state_dto.tt_rounds_won));

    receive_round(game_state_dto.round);
    receive_player_list(game_state_dto.players);

    return game_state_dto;
}

void Net::ClientProtocol::send_event(const DTO::EventDTO& event_dto) {
    skt.sendall(&event_dto.size, sizeof(event_dto.size));
    skt.sendall(event_dto.data.data(), event_dto.size);
}

std::list<GameInfoDTO> Net::ClientProtocol::receive_game_list() {
    uint8_t games_info_size;
    skt.recvall(&games_info_size, sizeof(games_info_size));

    std::list<GameInfoDTO> games_info;

    for (uint8_t i = 0; i < games_info_size; i++) {
        GameInfoDTO dto = GameInfoDTO();
        skt.recvall(&dto.id, sizeof(dto.id));

        uint8_t game_name_size;
        skt.recvall(&game_name_size, sizeof(game_name_size));

        std::vector<char> game_name(game_name_size);
        skt.recvall(game_name.data(), game_name_size);
        dto.name = std::string(game_name.begin(), game_name.end());

        skt.recvall(&dto.current_players, sizeof(dto.current_players));
        skt.recvall(&dto.max_players, sizeof(dto.max_players));

        uint8_t map_name_size;
        skt.recvall(&map_name_size, sizeof(map_name_size));

        std::vector<char> map_name(map_name_size);
        skt.recvall(map_name.data(), map_name_size);
        dto.map_name = std::string(map_name.begin(), map_name.end());

        games_info.push_back(dto);
    }

    return games_info;
}

std::list<std::string> Net::ClientProtocol::receive_map_list() {
    uint8_t maps_size;
    skt.recvall(&maps_size, sizeof(maps_size));

    std::list<std::string> maps;

    for (uint8_t i = 0; i < maps_size; i++) {
        uint8_t map_name_size;
        skt.recvall(&map_name_size, sizeof(map_name_size));

        std::vector<char> map_name(map_name_size);
        skt.recvall(map_name.data(), map_name_size);
        maps.push_back(std::string(map_name.begin(), map_name.end()));
    }

    return maps;
}

uint8_t Net::ClientProtocol::receive_player_id() {
    uint8_t player_id;
    skt.recvall(&player_id, sizeof(player_id));

    return player_id;
}

uint8_t Net::ClientProtocol::receive_team() {
    uint8_t team;
    skt.recvall(&team, sizeof(team));

    return team;
}

std::vector<std::vector<std::string>> Net::ClientProtocol::receive_map() {
    uint8_t map_size;
    skt.recvall(&map_size, sizeof(map_size));

    uint8_t row_size;
    skt.recvall(&row_size, sizeof(row_size));

    std::vector<std::vector<std::string>> map(map_size, std::vector<std::string>(row_size));

    for (uint8_t i = 0; i < map_size; i++) {
        for (uint8_t j = 0; j < row_size; j++) {
            uint8_t tile_size;
            skt.recvall(&tile_size, sizeof(tile_size));

            std::vector<char> tile(tile_size);
            skt.recvall(tile.data(), tile_size);
            map[i][j] = std::string(tile.begin(), tile.end());
        }
    }

    return map;
}
