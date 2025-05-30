#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <cstdint>
#include <list>
#include <string>
#include <utility>
#include <vector>

#include "client/game/dto_handler/event_dto_creator.h"
#include "common/DTO/event_dto.h"
#include "common/DTO/player_dto.h"
#include "common/DTO/game_info_dto.h"
#include "common/DTO/game_state_dto.h"
#include "common/socket.h"

namespace Net {

class ClientProtocol {
private:
    Socket skt;

    void receive_player_list(std::vector<DTO::PlayerDTO>& players);

    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

public:
    ClientProtocol(const std::string& host, const std::string& port):
            skt(host.c_str(), port.c_str()) {}

    explicit ClientProtocol(Socket& socket): skt(std::move(socket)) {}

    void send_event(const DTO::EventDTOCreator& event_dto_creator);
    DTO::GameStateDTO receive_match_state();
    std::list<GameInfoDTO> receive_game_list();
    std::list<std::string> receive_map_list();
    std::string receive_map();
    uint8_t receive_player_id();

    ClientProtocol(ClientProtocol&&) = default;
    ClientProtocol& operator=(ClientProtocol&&) = default;

    ~ClientProtocol() = default;
};

};  // namespace Net

#endif  // CLIENT_PROTOCOL_H
