#include "server_protocol.h"

#include <arpa/inet.h>
#include <string.h>
#include <iostream>

#include "common/dto/match_dto.h"
#include "common/event_type.h"

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
            uint8_t speed = uint8_t(data[3]);
            return MovementEvent(x, y, speed);
        }
        case Model::EventType::ROTATION: {
            int16_t angle_in_degrees = int16_t(data[1]) << 8 | int16_t(data[2]);
            return RotationEvent(angle_in_degrees);
        }
        case Model::EventType::USE_WEAPON: {
            return UseWeaponEvent(uint8_t(data[1]));
        }
        case Model::EventType::RELOAD_WEAPON: {
            return ReloadWeaponEvent(uint8_t(data[1]));
        }
        case Model::EventType::DROP_WEAPON: {
            return DropWeaponEvent(uint8_t(data[1]));
        }
        case Model::EventType::SWITCH_WEAPON: {
            return SwitchWeaponEvent(uint8_t(data[1]));
        }
        case Model::EventType::BUY_AMMO: {
            return BuyAmmoEvent(uint8_t(data[1]));
        }
        case Model::EventType::BUY_WEAPON: {
            return BuyEvent(uint8_t(data[1]));
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
        case Model::EventType::DEFUSE_BOMB: {
            return DefuseBombEvent(uint8_t(data[1]));
        }
        case Model::EventType::REQUEST_GAMES: {
            return ListGamesEvent();
        }
        case Model::EventType::REQUEST_MAPS: {
            return MapRequestEvent();
        }
        case Model::EventType::LEAVE_GAME: {
            return QuitEvent();
        }
        default:
            throw std::invalid_argument("Invalid event code");
    }
}

void ServerProtocol::send_weapon(const WeaponDTO& weapon) {
    uint16_t total_ammo = htons(weapon.total_ammo);

    peer.sendall(&weapon.id, sizeof(weapon.id));
    peer.sendall(&weapon.is_shooting, sizeof(weapon.is_shooting));
    peer.sendall(&weapon.is_reloading, sizeof(weapon.is_reloading));
    peer.sendall(&weapon.loaded_ammo, sizeof(weapon.loaded_ammo));
    peer.sendall(&total_ammo, sizeof(total_ammo));
}

void ServerProtocol::send_player_list(const std::vector<PlayerDTO>& players) {
    uint8_t players_size = players.size();
    peer.sendall(&players_size, sizeof(players_size));

    for (const auto& p: players) {
        uint8_t name_size = p.name.size();
        uint8_t player_id = p.player_id;
        uint16_t money = htons(p.money);
        uint16_t position_x = htons(p.position_x);
        uint16_t position_y = htons(p.position_y);
        uint16_t angle = htons(p.angle);

        peer.sendall(&name_size, sizeof(name_size));
        peer.sendall(p.name.c_str(), name_size);
        peer.sendall(&player_id, sizeof(player_id));
        peer.sendall(&p.skin_id, sizeof(p.skin_id));

        send_weapon(p.current_weapon);

        peer.sendall(&p.has_bomb, sizeof(p.has_bomb));
        peer.sendall(&p.health, sizeof(p.health));
        peer.sendall(&money, sizeof(money));
        peer.sendall(&position_x, sizeof(position_x));
        peer.sendall(&position_y, sizeof(position_y));
        peer.sendall(&angle, sizeof(angle));
    }
}

void ServerProtocol::send_dropped_weapons(const std::vector<DropWeaponDTO>& dropped_weapons) {
    uint8_t dropped_weapons_size = dropped_weapons.size();
    peer.sendall(&dropped_weapons_size, sizeof(dropped_weapons_size));

    for (const auto& dw: dropped_weapons) {
        send_weapon(dw.weapon);

        uint16_t position_x = htons(dw.position_x);
        uint16_t position_y = htons(dw.position_y);

        peer.sendall(&position_x, sizeof(position_x));
        peer.sendall(&position_y, sizeof(position_y));
    }
}

void ServerProtocol::send_match_state(const MatchCreator& mc) {
    DTO::MatchDTO match = mc.to_dto();
    peer.sendall(&match.is_valid, sizeof(match.is_valid));
    peer.sendall(&match.time_remaining, sizeof(match.time_remaining));
    peer.sendall(&match.round_number, sizeof(match.round_number));
    peer.sendall(&match.ct_wins, sizeof(match.ct_wins));
    peer.sendall(&match.tt_wins, sizeof(match.tt_wins));

    send_player_list(match.players);
    send_dropped_weapons(match.dropped_weapons);

    peer.sendall(&match.bomb_planted, sizeof(match.bomb_planted));
    peer.sendall(&match.bomb_defused, sizeof(match.bomb_defused));
    peer.sendall(&match.bomb_exploded, sizeof(match.bomb_exploded));
    peer.sendall(&match.winning_team, sizeof(match.winning_team));
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

void ServerProtocol::send_map(const std::string& map) {
    uint8_t map_name_size = map.size();
    peer.sendall(&map_name_size, sizeof(map_name_size));
    peer.sendall(map.c_str(), map_name_size);
}

void ServerProtocol::send_player_id(uint8_t player_id) {
    peer.sendall(&player_id, sizeof(player_id));
}
