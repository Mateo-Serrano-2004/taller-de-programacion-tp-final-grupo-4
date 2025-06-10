#ifndef CLIENT_GAME_CONTEXT_SHOP_CONTEXT_H
#define CLIENT_GAME_CONTEXT_SHOP_CONTEXT_H

#include <string>

#include <SDL2/SDL.h>

#include "common/definitions.h"

#include "base_context.h"

#include "handler/shop_event_handler_strategy.h"

#include "event/event.h"

#include "entity/vertical_pane.h"
#include "entity/button.h"

namespace Controller {
class GameController;
};

namespace Context {
class ShopContext: public BaseContext {
friend class Controller::ShopEventHandlerStrategy;

private:
    void build_button(View::Button& button, const std::string& weapon_name);
    void trigger_buttons(Shared<SDL_Event> event);

protected:
    SDL_Event placeholder;
    Controller::ShopEventHandlerStrategy strategy;
    View::VerticalPane background;
    View::Label label;
    View::Button buy_ak47;
    View::Button buy_m3;
    View::Button buy_awp;

    void update_size();

    void render() override;
    void dispatch_events() override;

public:
    ShopContext(Weak<Controller::GameController> controller);

    void handle_event(Shared<Model::Event> event) override;

    ~ShopContext() override = default;
};
};

#endif // CLIENT_GAME_CONTEXT_SHOP_CONTEXT_H
