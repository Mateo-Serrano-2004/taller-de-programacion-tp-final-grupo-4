#ifndef CLIENT_GAME_CONTROLLER_GAME_CONTROLLER_H
#define CLIENT_GAME_CONTROLLER_GAME_CONTROLLER_H

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
class TextureStorage;
};

namespace SDL2pp {
class Window;
class Renderer;
};

namespace Controller {
class GameStateManager;

class GameController: public BaseController {
protected:
    SharedQueue<Model::Event> sender_queue;
    Net::ClientProtocol* protocol;
    Shared<GameStateManager> game_state_manager;
    Sender sender;
    Receiver receiver;

    GameController(const GameController&) = delete;
    GameController& operator=(const GameController&) = delete;

    void process_event(Shared<Model::Event> event) override;

public:
    GameController(
        Shared<SDL2pp::Window> window,
        Shared<SDL2pp::Renderer> renderer,
        Shared<Model::TextureStorage> texture_storage,
        Shared<Context::ContextManager> context_manager,
        Net::ClientProtocol* protocol
    );

    void handle_event(Shared<Model::Event> event) override;

    Shared<GameStateManager> get_game_state_manager();

    GameController(GameController&&) = default;
    GameController& operator=(GameController&&) = default;

    ~GameController() override = default;
};
};

#endif // CLIENT_GAME_CONTROLLER_GAME_CONTROLLER_H
