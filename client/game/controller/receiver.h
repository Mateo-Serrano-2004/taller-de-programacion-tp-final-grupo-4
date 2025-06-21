#ifndef CLIENT_GAME_CONTROLLER_RECEIVER_H
#define CLIENT_GAME_CONTROLLER_RECEIVER_H

#include <atomic>

#include "common/DTO/game_state_dto.h"
#include "common/DTO/map_dto.h"
#include "common/DTO/player_id_dto.h"
#include "common/DTO/team_id_dto.h"
#include "common/definitions.h"
#include "common/thread.h"

namespace Net {
class ClientProtocol;
};


namespace Controller {
class GameController;
class GameStateManager;

class Receiver: public Thread {
protected:
    std::atomic<bool> keep_running;
    Weak<GameController> controller;
    Shared<Net::ClientProtocol> protocol;

    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;

    void update_game_state(DTO::GameStateDTO&& dto);
    void update_player_id(DTO::PlayerIDDTO&& dto);
    void update_current_team(DTO::TeamIDDTO&& dto);
    void generate_map(DTO::MapDTO&& dto);

    void receive_server_info();

public:
    Receiver(Weak<GameController> controller, Shared<Net::ClientProtocol> protocol);

    void run() override;

    ~Receiver() override;
};
};  // namespace Controller

#endif  // CLIENT_GAME_CONTROLLER_RECEIVER_H
