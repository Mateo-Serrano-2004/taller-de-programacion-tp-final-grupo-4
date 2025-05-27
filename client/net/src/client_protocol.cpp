#include "../include/client_protocol.h"

#include <vector>
#include <iostream>

#include <arpa/inet.h>

#include "common/DTO/event_dto.h"

void Net::ClientProtocol::send_event(const DTO::EventDTOCreator& event_dto_creator) {
    DTO::EventDTO event_dto = event_dto_creator.to_dto();
    skt.sendall(&event_dto.size, sizeof(event_dto.size));
    skt.sendall(event_dto.data.data(), event_dto.size);
}

void Net::ClientProtocol::receive_dropped_weapons(std::vector<DropWeaponDTO>& dropped_weapons) {
    uint8_t dropped_weapons_size;
    skt.recvall(&dropped_weapons_size, sizeof(dropped_weapons_size));

    dropped_weapons.resize(dropped_weapons_size);

    for (uint8_t i = 0; i < dropped_weapons_size; i++) {
        DropWeaponDTO dropped_weapon = DropWeaponDTO();
        skt.recvall(&dropped_weapon, sizeof(dropped_weapon));

        dropped_weapon.weapon.total_ammo = ntohs(dropped_weapon.weapon.total_ammo);
        dropped_weapon.position_x = ntohs(dropped_weapon.position_x);
        dropped_weapon.position_y = ntohs(dropped_weapon.position_y);

        dropped_weapons[i] = dropped_weapon;
    }
}

void Net::ClientProtocol::receive_player_list(std::vector<PlayerDTO>& players) {
    uint8_t players_size;
    skt.recvall(&players_size, sizeof(players_size));

    players.resize(players_size);

    for (uint8_t i = 0; i < players_size; i++) {
        PlayerDTO player;

        uint8_t name_size = 0;
        skt.recvall(&name_size, sizeof(name_size));

        std::vector<char> name(name_size);
        skt.recvall(name.data(), name_size);
        player.name = std::string(name.begin(), name.end());

        skt.recvall(&player.player_id, sizeof(player.player_id));

        skt.recvall(&player.skin_id, sizeof(player.skin_id));

        WeaponDTO current_weapon = WeaponDTO();
        skt.recvall(&current_weapon, sizeof(current_weapon));
        player.current_weapon = current_weapon;

        player.current_weapon.total_ammo = ntohs(player.current_weapon.total_ammo);

        skt.recvall(&player.has_bomb, sizeof(player.has_bomb));
        skt.recvall(&player.health, sizeof(player.health));

        skt.recvall(&player.money, sizeof(player.money));
        player.money = ntohs(player.money);

        skt.recvall(&player.position_x, sizeof(player.position_x));
        player.position_x = ntohs(player.position_x);

        skt.recvall(&player.position_y, sizeof(player.position_y));
        player.position_y = ntohs(player.position_y);

        skt.recvall(&player.angle, sizeof(player.angle));
        player.angle = ntohs(player.angle);

        players[i] = player;
    }
}

DTO::MatchDTO Net::ClientProtocol::receive_match_state() {
    DTO::MatchDTO match;

    skt.recvall(&match.is_valid, sizeof(match.is_valid));
    skt.recvall(&match.time_remaining, sizeof(match.time_remaining));
    skt.recvall(&match.round_number, sizeof(match.round_number));
    skt.recvall(&match.ct_wins, sizeof(match.ct_wins));
    skt.recvall(&match.tt_wins, sizeof(match.tt_wins));

    receive_player_list(match.players);
    receive_dropped_weapons(match.dropped_weapons);

    skt.recvall(&match.bomb_planted, sizeof(match.bomb_planted));
    skt.recvall(&match.bomb_defused, sizeof(match.bomb_defused));
    skt.recvall(&match.bomb_exploded, sizeof(match.bomb_exploded));
    skt.recvall(&match.winning_team, sizeof(match.winning_team));

    return match;
}

std::list<GameInfoDTO> Net::ClientProtocol::receive_game_list() {
    uint8_t games_info_size;
    skt.recvall(&games_info_size, sizeof(games_info_size));

    std::list<GameInfoDTO> games_info;
    games_info.resize(games_info_size);

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
    maps.resize(maps_size);

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
