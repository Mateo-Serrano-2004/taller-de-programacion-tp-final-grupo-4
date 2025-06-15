#ifndef CLIENT_GAME_CONTROLLER_GAME_CONTROLLER_H
#define CLIENT_GAME_CONTROLLER_GAME_CONTROLLER_H

#include "common/definitions.h"

#include "base_controller.h"
#include "receiver.h"
#include "sender.h"

namespace Net {
class ClientProtocol;
};

namespace Context {
class ContextManager;
};

namespace Model {
class Event;
class AssetManager;
};

namespace SDL2pp {
class Window;
class Renderer;
};

namespace Controller {
class GameStateManager;

class GameController: public BaseController {
protected:
    Shared<GameStateManager> game_state_manager;
    SharedQueue<Model::Event> sender_queue;
    Shared<Net::ClientProtocol> protocol;
    Unique<Sender> sender;
    Unique<Receiver> receiver;

    GameController(const GameController&) = delete;
    GameController& operator=(const GameController&) = delete;

    void process_event(Shared<Model::Event> event) override;

public:
    GameController(
        Shared<SDL2pp::Window> window,
        Shared<SDL2pp::Renderer> renderer,
        Shared<Model::AssetManager> asset_manager,
        Shared<Context::ContextManager> context_manager,
        Shared<Net::ClientProtocol> protocol
    );

    Shared<GameStateManager> get_game_state_manager();
    void build_game_state_manager(Weak<GameController> self);

    GameController(GameController&&) = default;
    GameController& operator=(GameController&&) = default;

    ~GameController() override = default;
};
};

#endif // CLIENT_GAME_CONTROLLER_GAME_CONTROLLER_H
