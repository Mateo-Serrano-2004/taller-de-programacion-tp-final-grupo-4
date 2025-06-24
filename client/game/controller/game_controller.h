#ifndef CLIENT_GAME_CONTROLLER_GAME_CONTROLLER_H
#define CLIENT_GAME_CONTROLLER_GAME_CONTROLLER_H

#include <map>

#include "common/definitions.h"
#include "common/event_type.h"

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
class TransferedEvent;
class AssetManager;
class AssetLoader;
};  // namespace Model

namespace SDL2pp {
class Window;
class Renderer;
};  // namespace SDL2pp

namespace Controller {
class GameStateManager;

class GameController: public BaseController {
protected:
    std::map<Model::EventType, Func<Shared<Model::Event>>> handlers;
    Shared<GameStateManager> game_state_manager;
    SharedQueue<Model::TransferedEvent> sender_queue;
    Shared<Net::ClientProtocol> protocol;
    Unique<Sender> sender;
    Unique<Receiver> receiver;

    GameController(const GameController&) = delete;
    GameController& operator=(const GameController&) = delete;

    void handle_switch_context(Shared<Model::Event> event);
    void handle_end_of_game(Shared<Model::Event>);
    void handle_update_player_id(Shared<Model::Event> event);
    void handle_update_role(Shared<Model::Event> event);
    void handle_generate_map(Shared<Model::Event> event);
    void handle_update_game_state(Shared<Model::Event> event);
    bool try_handle(Shared<Model::Event> event);
    void bind_handlers();

    void process_event(Shared<Model::Event> event) override;

public:
    GameController(Shared<SDL2pp::Window> window, Shared<SDL2pp::Renderer> renderer,
                   Shared<Model::AssetManager> asset_manager,
                   Shared<Model::AssetLoader> asset_loader,
                   Shared<Context::ContextManager> context_manager,
                   Shared<Net::ClientProtocol> protocol);

    Shared<GameStateManager> get_game_state_manager();
    void set_self_pointer(Weak<GameController> self);

    GameController(GameController&&) = default;
    GameController& operator=(GameController&&) = default;

    ~GameController() override = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_CONTROLLER_GAME_CONTROLLER_H
