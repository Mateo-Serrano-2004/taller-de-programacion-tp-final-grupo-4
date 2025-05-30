#include "client_protocol.h"

#include <vector>

#include <arpa/inet.h>

#include "common/DTO/event_dto.h"

void Net::ClientProtocol::send_event(const DTO::EventDTOCreator& event_dto_creator) {
    DTO::EventDTO event_dto = event_dto_creator.to_dto();
    skt.sendall(&event_dto.size, sizeof(event_dto.size));
    skt.sendall(event_dto.data.data(), event_dto.size);
}

void Net::ClientProtocol::receive_player_list(std::vector<DTO::PlayerDTO>& players) {
    uint8_t players_size;
    skt.recvall(&players_size, sizeof(players_size));

    for (uint8_t i = 0; i < players_size; i++) {
        uint8_t name_size;
        std::vector<char> name;
        short_id_t player_id;
        short_id_t skin_id;
        short_id_t skin_piece;
        angle_t angle;
        coord_t position_x;
        coord_t position_y;

        skt.recvall(&name_size, sizeof(name_size));

        name.resize(name_size);
        skt.recvall(name.data(), name_size);

        skt.recvall(&player_id, sizeof(player_id));

        skt.recvall(&skin_id, sizeof(skin_id));

        skt.recvall(&skin_piece, sizeof(skin_piece));

        skt.recvall(&position_x, sizeof(position_x));
        position_x = ntohs(position_x);

        skt.recvall(&position_y, sizeof(position_y));
        position_y = ntohs(position_y);

        skt.recvall(&angle, sizeof(angle));
        angle = ntohs(angle);

        players.emplace_back(
            player_id,
            skin_id,
            skin_piece,
            angle,
            position_x,
            position_y,
            std::string(name.begin(), name.end())
        );
    }
}

DTO::GameStateDTO Net::ClientProtocol::receive_match_state() {
    DTO::GameStateDTO match;

    skt.recvall(&match.is_valid, sizeof(match.is_valid));
    receive_player_list(match.players);

    return match;
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

std::string Net::ClientProtocol::receive_map() {
    uint8_t map_name_size;
    skt.recvall(&map_name_size, sizeof(map_name_size));

    std::vector<char> map_name(map_name_size);
    skt.recvall(map_name.data(), map_name_size);

    return std::string(map_name.begin(), map_name.end());
}

uint8_t Net::ClientProtocol::receive_player_id() {
    uint8_t player_id;
    skt.recvall(&player_id, sizeof(player_id));

    return player_id;
}
