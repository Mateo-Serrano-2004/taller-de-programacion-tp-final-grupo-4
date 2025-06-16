#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <cstdint>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include "common/DTO/event_dto.h"
#include "common/DTO/game_info_dto.h"
#include "common/DTO/game_state_dto.h"
#include "common/DTO/player_dto.h"
#include "common/DTO/weapon_dto.h"
#include "common/DTO/round_dto.h"
#include "common/socket.h"

namespace Net {

class ClientProtocol {
private:
    Socket skt;

    void receive_weapon(DTO::WeaponDTO& weapon);
    void receive_player(DTO::PlayerDTO& player);
    void receive_player_list(std::vector<DTO::PlayerDTO>& players);
    DTO::RoundDTO receive_round(DTO::RoundDTO& round);

    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

public:
    ClientProtocol(const std::string& host, const std::string& port):
            skt(host.c_str(), port.c_str()) {}

    explicit ClientProtocol(Socket& socket): skt(std::move(socket)) {}

    void send_event(const DTO::EventDTO& event_dto);

    DTO::GameStateDTO receive_match_state();
    std::list<GameInfoDTO> receive_game_list();
    std::list<std::string> receive_map_list();
    std::vector<std::vector<std::string>> receive_map();
    uint8_t receive_player_id();
    uint8_t receive_team();

    ClientProtocol(ClientProtocol&&) = default;
    ClientProtocol& operator=(ClientProtocol&&) = default;

    ~ClientProtocol() = default;
};

};  // namespace Net

#endif  // CLIENT_PROTOCOL_H
