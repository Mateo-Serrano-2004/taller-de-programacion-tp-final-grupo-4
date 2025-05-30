#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "common/DTO/game_info_dto.h"
#include "common/socket.h"
#include "server/events/events.h"
#include "common/DTO/game_state_dto.h"
#include "common/DTO/player_dto.h"

class ServerProtocol {
private:
    Socket peer;

    void send_player_list(const std::vector<DTO::PlayerDTO>& players);

    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

public:
    explicit ServerProtocol(Socket& peer): peer(std::move(peer)) {}

    EventVariant receive_event();
    void send_player_id(uint8_t player_id);
    void send_match_state(const DTO::GameStateDTO& game_state);
    void send_all_maps_names(const std::vector<std::string>& maps);
    void send_games(const std::vector<GameInfoDTO>& games);
    void send_map(const std::string& map);

    ServerProtocol(ServerProtocol&&) = default;
    ServerProtocol& operator=(ServerProtocol&&) = default;

    ~ServerProtocol() = default;
};

#endif  // SERVER_PROTOCOL_H
