#include "client_protocol.h"

#include <cstdint>
#include <vector>

#include <arpa/inet.h>

#include "common/DTO/dto_code.h"
#include "common/DTO/event_dto.h"

void Net::ClientProtocol::receive_dropped_weapon(DTO::DropWeaponDTO& dropped_weapon) {
    skt.recvall(&dropped_weapon.weapon_id, sizeof(dropped_weapon.weapon_id));
    coord_t position_x, position_y;
    skt.recvall(&position_x, sizeof(position_x));
    skt.recvall(&position_y, sizeof(position_y));
    dropped_weapon.position_x = ntohs(position_x);
    dropped_weapon.position_y = ntohs(position_y);
}

void Net::ClientProtocol::receive_dropped_weapons_list(
        std::vector<DTO::DropWeaponDTO>& dropped_weapons) {
    uint8_t dropped_weapons_size;
    skt.recvall(&dropped_weapons_size, sizeof(dropped_weapons_size));

    for (uint8_t i = 0; i < dropped_weapons_size; i++) {
        DTO::DropWeaponDTO dropped_weapon;
        receive_dropped_weapon(dropped_weapon);
        dropped_weapons.push_back(dropped_weapon);
    }
}

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
    skt.recvall(&player.defusing_bomb, sizeof(player.defusing_bomb));
    skt.recvall(&player.health, sizeof(player.health));
    skt.recvall(&player.reloading, sizeof(player.reloading));
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

    skt.recvall(&player.kills, sizeof(player.kills));
    skt.recvall(&player.deaths, sizeof(player.deaths));
    skt.recvall(&player.planting_progress, sizeof(player.planting_progress));
    skt.recvall(&player.has_bomb, sizeof(player.has_bomb));
    skt.recvall(&player.has_hit, sizeof(player.has_hit));

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

void Net::ClientProtocol::receive_round(DTO::RoundDTO& round) {
    skt.recvall(&round.state, sizeof(round.state));
    skt.recvall(&round.ended, sizeof(round.ended));
    skt.recvall(&round.time_left, sizeof(round.time_left));
    skt.recvall(&round.winner, sizeof(round.winner));
    skt.recvall(&round.bomb_planted, sizeof(round.bomb_planted));
    skt.recvall(&round.bomb_defused, sizeof(round.bomb_defused));

    coord_t bomb_position_x, bomb_position_y;
    skt.recvall(&bomb_position_x, sizeof(bomb_position_x));
    skt.recvall(&bomb_position_y, sizeof(bomb_position_y));

    skt.recvall(&round.defusing_progress, sizeof(round.defusing_progress));

    round.bomb_position.set_x(ntohs(bomb_position_x));
    round.bomb_position.set_y(ntohs(bomb_position_y));

    round.time_left = htons(round.time_left);

    receive_dropped_weapons_list(round.dropped_weapons);
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

DTO::PlayerIDDTO Net::ClientProtocol::receive_player_id() {
    DTO::PlayerIDDTO player_id;
    skt.recvall(&player_id.id, sizeof(player_id.id));

    return player_id;
}

DTO::TeamIDDTO Net::ClientProtocol::receive_team() {
    DTO::TeamIDDTO team;
    skt.recvall(&team.id, sizeof(team.id));

    return team;
}

DTO::MapDTO Net::ClientProtocol::receive_map() {
    DTO::MapDTO map;
    skt.recvall(&map.count_of_columns, sizeof(map.count_of_columns));
    skt.recvall(&map.count_of_rows, sizeof(map.count_of_rows));

    map.map = PathMap(map.count_of_rows, PathRow(map.count_of_columns));

    for (uint8_t i = 0; i < map.count_of_rows; i++) {
        for (uint8_t j = 0; j < map.count_of_columns; j++) {
            uint8_t path_size;
            skt.recvall(&path_size, sizeof(path_size));

            std::vector<char> path(path_size);
            skt.recvall(path.data(), path_size);
            map.map[i][j] = std::string(path.begin(), path.end());
        }
    }

    return map;
}

DTO::MapNameListDTO Net::ClientProtocol::receive_map_list() {
    DTO::MapNameListDTO map_name;
    uint8_t maps_size;
    skt.recvall(&maps_size, sizeof(maps_size));

    for (uint8_t i = 0; i < maps_size; i++) {
        uint8_t map_name_size;
        skt.recvall(&map_name_size, sizeof(map_name_size));

        std::vector<char> name(map_name_size);
        skt.recvall(name.data(), map_name_size);
        map_name.maps_names.push_back(std::string(name.begin(), name.end()));
    }

    return map_name;
}

void Net::ClientProtocol::receive_game_info(DTO::GameInfoDTO& dto) {
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
}

DTO::GameListDTO Net::ClientProtocol::receive_game_list() {
    DTO::GameListDTO games;

    uint8_t size;
    skt.recvall(&size, sizeof(size));


    for (uint8_t i = 0; i < size; i++) {
        DTO::GameInfoDTO dto;
        receive_game_info(dto);
        games.games.push_back(dto);
    }

    return games;
}

void Net::ClientProtocol::send_event(const DTO::EventDTO& event_dto) {
    skt.sendall(&event_dto.size, sizeof(event_dto.size));
    skt.sendall(event_dto.data.data(), event_dto.size);
}

DTO::ConfigDTO Net::ClientProtocol::receive_config() {
    DTO::ConfigDTO config;

    skt.recvall(&config.width, sizeof(config.width));
    skt.recvall(&config.height, sizeof(config.height));
    skt.recvall(&config.opacity, sizeof(config.opacity));
    skt.recvall(&config.angle, sizeof(config.angle));
    skt.recvall(&config.ratio, sizeof(config.ratio));

    config.width = ntohs(config.width);
    config.height = ntohs(config.height);
    config.angle = ntohs(config.angle);
    config.ratio = ntohs(config.ratio);

    return config;
}

DTO::DTOVariant Net::ClientProtocol::receive_variant() {
    DTO::DTOCode code;
    skt.recvall(&code, sizeof(code));

    switch (code) {
        case DTO::DTOCode::GAME_STATE:
            return receive_match_state();
        case DTO::DTOCode::PLAYER_ID:
            return receive_player_id();
        case DTO::DTOCode::TEAM_ID:
            return receive_team();
        case DTO::DTOCode::MAP:
            return receive_map();
        case DTO::DTOCode::MAP_NAMES_LIST:
            return receive_map_list();
        case DTO::DTOCode::GAMES_LIST:
            return receive_game_list();
        case DTO::DTOCode::CONFIG:
            return receive_config();
        default:
            throw std::runtime_error("Invalid DTO code received");
    }
}
