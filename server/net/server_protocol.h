#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <cstdint>
#include <string>
#include <utility>
#include <vector>
#include <mutex>

#include "common/DTO/game_info_dto.h"
#include "common/DTO/game_state_dto.h"
#include "common/DTO/player_dto.h"
#include "common/socket.h"
#include "server/events/events.h"

class ServerProtocol {
private:
    std::mutex mutex;
    Socket peer;

    void send_weapon(const DTO::WeaponDTO& weapon_dto);
    void send_player(const DTO::PlayerDTO& player);
    void send_player_list(const std::vector<DTO::PlayerDTO>& players);
    void send_round(const DTO::RoundDTO& round_dto);

    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

public:
    explicit ServerProtocol(Socket& peer): peer(std::move(peer)) {}

    EventVariant receive_event();
    void send_player_id(uint8_t player_id);
    void send_game_state(const DTO::GameStateDTO& game_state);
    void send_all_maps_names(const std::vector<std::string>& maps);
    void send_games(const std::vector<GameInfoDTO>& games);

    ServerProtocol(ServerProtocol&&) = default;
    ServerProtocol& operator=(ServerProtocol&&) = default;

    ~ServerProtocol() = default;
};

#endif  // SERVER_PROTOCOL_H
