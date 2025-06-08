#include "server_protocol.h"

#include <iostream>

#include <arpa/inet.h>
#include <string.h>

#include "common/DTO/game_state_dto.h"
#include "common/DTO/player_dto.h"
#include "common/DTO/weapon_dto.h"
#include "common/definitions.h"
#include "common/event_type.h"
#include "common/weapon_type.h"

EventVariant ServerProtocol::receive_event() {
    uint8_t size;
    peer.recvall(&size, sizeof(size));

    std::vector<char> data(size);
    peer.recvall(data.data(), size);

    uint8_t event = uint8_t(data[0]);

    switch (event) {
        case Model::EventType::MOVEMENT: {
            int8_t x = int8_t(data[1]);
            int8_t y = int8_t(data[2]);
            return MovementEvent(x, y);
        }
        case Model::EventType::STOP_MOVEMENT: {
            bool is_horizontal = int8_t(data[1]);
            return StopMovementEvent(is_horizontal);
        }
        case Model::EventType::ROTATION: {
            angle_t big_endian_angle;
            memcpy(&big_endian_angle, data.data() + 1, 2);
            angle_t angle = ntohs(big_endian_angle);
            return RotationEvent(angle);
        }
        case Model::EventType::USERNAME: {
            uint8_t username_size = uint8_t(data[1]);
            std::string username(data.data() + 2, username_size);
            return UsernameEvent(username);
        }
        case Model::EventType::CREATE_GAME: {
            uint8_t party_name_size = uint8_t(data[1]);
            uint8_t map_name_size = uint8_t(data[2]);

            std::string party_name(data.data() + 2, party_name_size);
            std::string map_name(data.data() + 2 + party_name_size, map_name_size);

            return CreateGameEvent(party_name, map_name);
        }
        case Model::EventType::JOIN_GAME: {
            return JoinGameEvent(uint8_t(data[1]));
        }
        case Model::EventType::REQUEST_GAMES_LIST: {
            return ListGamesEvent();
        }
        case Model::EventType::REQUEST_MAPS: {
            return MapRequestEvent();
        }
        case Model::EventType::LEAVE_GAME: {
            return LeaveGameEvent();
        }
        case Model::EventType::PICK_SPRITE: {
            uint8_t sprite_id = uint8_t(data[1]);
            return PickSpriteEvent(sprite_id);
        }
        case Model::EventType::SWITCH_WEAPON: {
            WeaponType weapon_type = WeaponType(data[1]);
            return SwitchWeaponEvent(weapon_type);
        }
        default:
            throw std::invalid_argument("Invalid event code");
    }
}

void ServerProtocol::send_player_list(const std::vector<DTO::PlayerDTO>& players) {
    uint8_t players_size = players.size();
    peer.sendall(&players_size, sizeof(players_size));

    for (const auto& p: players) {
        uint8_t name_size = static_cast<uint8_t>(p.name.size());
        coord_t position_x = htons(p.position_x);
        coord_t position_y = htons(p.position_y);
        angle_t angle = htons(p.angle);

        peer.sendall(&name_size, sizeof(name_size));
        peer.sendall(p.name.c_str(), name_size);
        peer.sendall(&p.player_id, sizeof(p.player_id));
        peer.sendall(&p.skin_id, sizeof(p.skin_id));
        peer.sendall(&p.skin_piece, sizeof(p.skin_piece));
        peer.sendall(&position_x, sizeof(position_x));
        peer.sendall(&position_y, sizeof(position_y));
        peer.sendall(&angle, sizeof(angle));

        send_weapon(p);
    }
}

void ServerProtocol::send_weapon(const DTO::PlayerDTO& player_dto) {
    DTO::WeaponDTO weapon_dto = player_dto.weapon_dto;

    peer.sendall(&weapon_dto.weapon_id, sizeof(weapon_dto.weapon_id));
    peer.sendall(&weapon_dto.loaded_ammo, sizeof(weapon_dto.loaded_ammo));
    peer.sendall(&weapon_dto.total_ammo, sizeof(weapon_dto.total_ammo));
}

void ServerProtocol::send_game_state(const DTO::GameStateDTO& game_state_dto) {
    peer.sendall(&game_state_dto.is_valid, sizeof(game_state_dto.is_valid));
    send_player_list(game_state_dto.players);

    uint16_t time_left = htons(game_state_dto.time_left);
    peer.sendall(&time_left, sizeof(time_left));
}

void ServerProtocol::send_all_maps_names(const std::vector<std::string>& maps) {
    uint8_t maps_size = maps.size();
    peer.sendall(&maps_size, sizeof(maps_size));

    for (const auto& map: maps) {
        uint8_t map_name_size = map.size();
        peer.sendall(&map_name_size, sizeof(map_name_size));
        peer.sendall(map.c_str(), map_name_size);
    }
}

void ServerProtocol::send_games(const std::vector<GameInfoDTO>& games) {
    uint8_t games_size = games.size();
    peer.sendall(&games_size, sizeof(games_size));

    for (const auto& game: games) {
        uint8_t game_id = game.id;
        uint8_t game_name = game.name.size();
        uint8_t map_name_size = game.map_name.size();

        peer.sendall(&game_id, sizeof(game_id));

        peer.sendall(&game_name, sizeof(game_name));
        peer.sendall(game.name.c_str(), game_name);

        peer.sendall(&game.current_players, sizeof(game.current_players));
        peer.sendall(&game.max_players, sizeof(game.max_players));

        peer.sendall(&map_name_size, sizeof(map_name_size));
        peer.sendall(game.map_name.c_str(), map_name_size);
    }
}

void ServerProtocol::send_player_id(uint8_t player_id) {
    peer.sendall(&player_id, sizeof(player_id));
}
