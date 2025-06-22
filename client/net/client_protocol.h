#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <cstdint>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include "common/DTO/dto_variant.h"
#include "common/DTO/event_dto.h"
#include "common/socket.h"

namespace Net {

class ClientProtocol {
private:
    Socket skt;

    void receive_weapon(DTO::WeaponDTO& weapon);
    void receive_player(DTO::PlayerDTO& player);
    void receive_player_list(std::vector<DTO::PlayerDTO>& players);
    void receive_round(DTO::RoundDTO& round);
    void receive_dropped_weapon(DTO::DropWeaponDTO& dropped_weapon);
    void receive_dropped_weapons_list(std::vector<DTO::DropWeaponDTO>& dropped_weapons);

    DTO::GameStateDTO receive_match_state();
    DTO::PlayerIDDTO receive_player_id();
    DTO::TeamIDDTO receive_team();
    DTO::MapDTO receive_map();
    DTO::MapNameListDTO receive_map_list();
    DTO::ConfigDTO receive_config();

    void receive_game_info(DTO::GameInfoDTO& dto);
    DTO::GameListDTO receive_game_list();

    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

public:
    ClientProtocol(const std::string& host, const std::string& port):
            skt(host.c_str(), port.c_str()) {}

    explicit ClientProtocol(Socket& socket): skt(std::move(socket)) {}

    void send_event(const DTO::EventDTO& event_dto);

    DTO::DTOVariant receive_variant();

    ClientProtocol(ClientProtocol&&) = default;
    ClientProtocol& operator=(ClientProtocol&&) = default;

    ~ClientProtocol() = default;
};

};  // namespace Net

#endif  // CLIENT_PROTOCOL_H
