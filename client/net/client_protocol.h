#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <cstdint>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include "common/DTO/event_dto.h"
#include "common/DTO/game_info_dto.h"
#include "common/DTO/match_dto.h"
#include "common/socket.h"

#include "client/game/dto_handler/event_dto_creator.h"

namespace Net {

class ClientProtocol {
private:
    Socket skt;

    void receive_player_list(std::vector<PlayerDTO>& players);
    void receive_dropped_weapons(std::vector<DropWeaponDTO>& dropped_weapons);

    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

public:
    ClientProtocol(const std::string& host, const std::string& port):
            skt(host.c_str(), port.c_str()) {
            }

    explicit ClientProtocol(Socket& socket): skt(std::move(socket)) {
        std::cout << "Protocol\n";
    }

    void send_event(const DTO::EventDTOCreator& event_dto_creator);
    DTO::MatchDTO receive_match_state();
    std::list<GameInfoDTO> receive_game_list();
    std::list<std::string> receive_map_list();
    std::string receive_map();
    uint8_t receive_player_id();

    ClientProtocol(ClientProtocol&&) = default;
    ClientProtocol& operator=(ClientProtocol&&) = default;

    ~ClientProtocol() = default;
};

};

#endif  // CLIENT_PROTOCOL_H
