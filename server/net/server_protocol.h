#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "common/DTO/drop_weapon_dto.h"
#include "common/DTO/dto_variant.h"
#include "common/DTO/game_info_dto.h"
#include "common/DTO/game_state_dto.h"
#include "common/DTO/player_dto.h"
#include "common/socket.h"
#include "server/events/events.h"

class ServerProtocol {
private:
    Socket peer;

    void send_weapon(const DTO::WeaponDTO& weapon_dto);
    void send_player(const DTO::PlayerDTO& player);
    void send_player_list(const std::vector<DTO::PlayerDTO>& players);
    void send_round(const DTO::RoundDTO& round_dto);
    void send_config(const DTO::ConfigDTO& config_dto);
    void send_player_id(const DTO::PlayerIDDTO& player_id_dto);
    void send_team_id(const DTO::TeamIDDTO& team_id_dto);
    void send_game_state(const DTO::GameStateDTO& game_state);
    void send_all_maps_names(const DTO::MapNameListDTO& maps);
    void send_games(const DTO::GameListDTO& game_list_dto);
    void send_map(const DTO::MapDTO& map_dto);
    void send_dropped_weapons(const std::vector<DTO::DropWeaponDTO>& dropped_weapons);

    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

public:
    explicit ServerProtocol(Socket&& peer): peer(std::move(peer)) {}
    void close_socket();
    EventVariant receive_event();
    void send_variant(const DTO::DTOVariant& variant);

    ServerProtocol(ServerProtocol&&) = default;
    ServerProtocol& operator=(ServerProtocol&&) = default;

    ~ServerProtocol() = default;
};

#endif  // SERVER_PROTOCOL_H
