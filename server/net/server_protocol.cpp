#include "server_protocol.h"

#include <exception>
#include <mutex>
#include <variant>

#include <arpa/inet.h>
#include <string.h>

#include "common/DTO/dto_code.h"
#include "common/DTO/weapon_dto.h"
#include "common/definitions.h"
#include "common/event_type.h"
#include "common/overloaded.h"
#include "common/role_id.h"
#include "common/slot_id.h"

EventVariant ServerProtocol::receive_event() {
    uint8_t size;
    peer.recvall(&size, sizeof(size));

    std::vector<char> data(size);
    peer.recvall(data.data(), size);

    auto event = static_cast<Model::EventType>(data[0]);

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

            std::string party_name(data.data() + 3, party_name_size);
            std::string map_name(data.data() + 3 + party_name_size, map_name_size);

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
        case Model::EventType::QUIT: {
            return QuitEvent();
        }
        case Model::EventType::PICK_ROLE: {
            Model::RoleID role_id = Model::RoleID(data[1]);
            return PickRoleEvent(role_id);
        }
        case Model::EventType::SWITCH_WEAPON: {
            Model::SlotID slot_id = Model::SlotID(data[1]);
            return SwitchWeaponEvent(slot_id);
        }
        case Model::EventType::USE_WEAPON: {
            return UseWeaponEvent();
        }
        case Model::EventType::STOP_USING_WEAPON: {
            return StopUsingWeaponEvent();
        }
        case Model::EventType::BUY_WEAPON: {
            Model::WeaponID weapon_id = Model::WeaponID(data[1]);
            return BuyEvent(weapon_id);
        }
        case Model::EventType::DEFUSE_BOMB: {
            return DefuseBombEvent();
        }
        case Model::EventType::STOP_DEFUSING_BOMB: {
            return StopDefusingBombEvent();
        }
        case Model::EventType::DROP_WEAPON: {
            return DropWeaponEvent();
        }
        case Model::EventType::RELOAD_WEAPON: {
            return ReloadWeaponEvent();
        }
        case Model::EventType::BUY_AMMO: {
            Model::SlotID slot_id = Model::SlotID(data[1]);
            return BuyAmmoEvent(slot_id);
        }
        default:
            throw std::invalid_argument("Invalid event code");
    }
}

void ServerProtocol::send_variant(const DTO::DTOVariant& variant) {
    std::visit(overloaded{
                       [this](const DTO::GameStateDTO& d) { send_game_state(d); },
                       [this](const DTO::PlayerIDDTO& d) { send_player_id(d); },
                       [this](const DTO::TeamIDDTO& d) { send_team_id(d); },
                       [this](const DTO::MapDTO& d) { send_map(d); },
                       [this](const DTO::MapNameListDTO& d) { send_all_maps_names(d); },
                       [this](const DTO::GameListDTO& d) { send_games(d); },
                       [this](const DTO::ConfigDTO& d) { send_config(d); },
               },
               variant);
}

void ServerProtocol::send_dropped_weapons(const std::vector<DTO::DropWeaponDTO>& dropped_weapons) {
    uint8_t dropped_weapons_size = dropped_weapons.size();
    peer.sendall(&dropped_weapons_size, sizeof(dropped_weapons_size));

    for (const auto& dropped_weapon: dropped_weapons) {
        peer.sendall(&dropped_weapon.weapon_id, sizeof(dropped_weapon.weapon_id));
        coord_t position_x = htons(dropped_weapon.position_x);
        coord_t position_y = htons(dropped_weapon.position_y);
        peer.sendall(&position_x, sizeof(position_x));
        peer.sendall(&position_y, sizeof(position_y));
    }
}

void ServerProtocol::send_weapon(const DTO::WeaponDTO& weapon_dto) {
    uint16_t total_ammo = htons(weapon_dto.total_ammo);

    peer.sendall(&weapon_dto.weapon_id, sizeof(weapon_dto.weapon_id));
    peer.sendall(&weapon_dto.loaded_ammo, sizeof(weapon_dto.loaded_ammo));
    peer.sendall(&total_ammo, sizeof(total_ammo));
}

void ServerProtocol::send_player(const DTO::PlayerDTO& player) {
    uint8_t name_size = static_cast<uint8_t>(player.name.size());
    angle_t angle = htons(player.angle);
    uint16_t money = htons(player.money);
    coord_t position_x = htons(player.position_x);
    coord_t position_y = htons(player.position_y);

    peer.sendall(&player.player_id, sizeof(player.player_id));
    peer.sendall(&player.role_id, sizeof(player.role_id));
    peer.sendall(&player.shooting, sizeof(player.shooting));
    peer.sendall(&player.defusing_bomb, sizeof(player.defusing_bomb));
    peer.sendall(&player.health, sizeof(player.health));
    peer.sendall(&player.reloading, sizeof(player.reloading));
    peer.sendall(&player.team, sizeof(player.team));
    peer.sendall(&angle, sizeof(angle));
    peer.sendall(&money, sizeof(money));
    peer.sendall(&position_x, sizeof(position_x));
    peer.sendall(&position_y, sizeof(position_y));
    peer.sendall(&name_size, sizeof(name_size));
    peer.sendall(player.name.c_str(), name_size);
    peer.sendall(&player.kills, sizeof(player.kills));
    peer.sendall(&player.deaths, sizeof(player.deaths));
    peer.sendall(&player.planting_progress, sizeof(player.planting_progress));
    peer.sendall(&player.has_bomb, sizeof(player.has_bomb));
    peer.sendall(&player.has_hit, sizeof(player.has_hit));

    send_weapon(player.weapon_dto);
}

void ServerProtocol::send_player_list(const std::vector<DTO::PlayerDTO>& players) {
    uint8_t players_size = players.size();
    peer.sendall(&players_size, sizeof(players_size));

    for (const auto& p: players) send_player(p);
}

void ServerProtocol::send_round(const DTO::RoundDTO& round_dto) {
    uint16_t time_left = htons(round_dto.time_left);
    peer.sendall(&round_dto.state, sizeof(round_dto.state));
    peer.sendall(&round_dto.ended, sizeof(round_dto.ended));
    peer.sendall(&time_left, sizeof(time_left));
    peer.sendall(&round_dto.winner, sizeof(round_dto.winner));
    peer.sendall(&round_dto.bomb_planted, sizeof(round_dto.bomb_planted));
    peer.sendall(&round_dto.bomb_defused, sizeof(round_dto.bomb_defused));
    coord_t bomb_position_x = htons(round_dto.bomb_position.get_x());
    coord_t bomb_position_y = htons(round_dto.bomb_position.get_y());
    peer.sendall(&bomb_position_x, sizeof(bomb_position_x));
    peer.sendall(&bomb_position_y, sizeof(bomb_position_y));
    peer.sendall(&round_dto.defusing_progress, sizeof(round_dto.defusing_progress));

    send_dropped_weapons(round_dto.dropped_weapons);
}

void ServerProtocol::send_game_state(const DTO::GameStateDTO& game_state_dto) {
    DTO::DTOCode code = DTO::DTOCode::GAME_STATE;
    peer.sendall(&code, sizeof(code));

    peer.sendall(&game_state_dto.game_state, sizeof(game_state_dto.game_state));
    peer.sendall(&game_state_dto.ended, sizeof(game_state_dto.ended));
    peer.sendall(&game_state_dto.winner, sizeof(game_state_dto.winner));
    peer.sendall(&game_state_dto.ct_rounds_won, sizeof(game_state_dto.ct_rounds_won));
    peer.sendall(&game_state_dto.tt_rounds_won, sizeof(game_state_dto.tt_rounds_won));
    send_round(game_state_dto.round);
    send_player_list(game_state_dto.players);
}

void ServerProtocol::send_all_maps_names(const DTO::MapNameListDTO& maps) {
    DTO::DTOCode code = DTO::DTOCode::MAP_NAMES_LIST;
    peer.sendall(&code, sizeof(code));

    uint8_t size = static_cast<uint8_t>(maps.maps_names.size());

    peer.sendall(&size, sizeof(size));

    for (const auto& map: maps.maps_names) {
        uint8_t map_name_size = static_cast<uint8_t>(map.size());
        peer.sendall(&map_name_size, sizeof(map_name_size));
        peer.sendall(map.c_str(), map_name_size);
    }
}

void ServerProtocol::send_games(const DTO::GameListDTO& game_list_dto) {
    DTO::DTOCode code = DTO::DTOCode::GAMES_LIST;
    peer.sendall(&code, sizeof(code));

    uint8_t size = static_cast<uint8_t>(game_list_dto.games.size());
    peer.sendall(&size, sizeof(size));

    for (const auto& game: game_list_dto.games) {
        uint8_t game_id = game.id;
        uint8_t game_name = static_cast<uint8_t>(game.name.size());
        uint8_t map_name_size = static_cast<uint8_t>(game.map_name.size());

        peer.sendall(&game_id, sizeof(game_id));

        peer.sendall(&game_name, sizeof(game_name));
        peer.sendall(game.name.c_str(), game_name);

        peer.sendall(&game.current_players, sizeof(game.current_players));
        peer.sendall(&game.max_players, sizeof(game.max_players));

        peer.sendall(&map_name_size, sizeof(map_name_size));
        peer.sendall(game.map_name.c_str(), map_name_size);
    }
}

void ServerProtocol::send_player_id(const DTO::PlayerIDDTO& player_id_dto) {
    DTO::DTOCode code = DTO::DTOCode::PLAYER_ID;
    peer.sendall(&code, sizeof(code));
    peer.sendall(&player_id_dto.id, sizeof(player_id_dto.id));
}

void ServerProtocol::send_team_id(const DTO::TeamIDDTO& team_id_dto) {
    DTO::DTOCode code = DTO::DTOCode::TEAM_ID;
    peer.sendall(&code, sizeof(code));
    peer.sendall(&team_id_dto.id, sizeof(team_id_dto.id));
}

void ServerProtocol::send_map(const DTO::MapDTO& map_dto) {
    DTO::DTOCode code = DTO::DTOCode::MAP;
    peer.sendall(&code, sizeof(code));

    auto map = map_dto.map;
    uint8_t cols = map_dto.count_of_columns;
    uint8_t rows = map_dto.count_of_rows;

    peer.sendall(&cols, sizeof(cols));
    peer.sendall(&rows, sizeof(rows));

    for (const auto& row: map) {
        for (const auto& path: row) {
            uint8_t path_size = static_cast<uint8_t>(path.size());
            peer.sendall(&path_size, sizeof(path_size));
            peer.sendall(path.c_str(), path_size);
        }
    }
}

void ServerProtocol::send_config(const DTO::ConfigDTO& config_dto) {
    DTO::DTOCode code = DTO::DTOCode::CONFIG;
    peer.sendall(&code, sizeof(code));

    DTO::ConfigDTO config = config_dto;
    config.width = htons(config.width);
    config.height = htons(config.height);
    config.angle = htons(config.angle);
    config.ratio = htons(config.ratio);

    peer.sendall(&config.width, sizeof(config.width));
    peer.sendall(&config.height, sizeof(config.height));
    peer.sendall(&config.opacity, sizeof(config.opacity));
    peer.sendall(&config.angle, sizeof(config.angle));
    peer.sendall(&config.ratio, sizeof(config.ratio));
}

void ServerProtocol::close_socket() {
    try {
        peer.shutdown(2);
    } catch (const std::exception&) {}
}
