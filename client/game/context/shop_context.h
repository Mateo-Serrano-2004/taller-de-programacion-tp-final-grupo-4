#ifndef CLIENT_GAME_CONTEXT_SHOP_CONTEXT_H
#define CLIENT_GAME_CONTEXT_SHOP_CONTEXT_H

#include <cstdint>
#include <string>

#include "common/definitions.h"
#include "common/weapon_id.h"
#include "entity/button.h"
#include "entity/vertical_pane.h"
#include "event/event.h"
#include "handler/shop_event_handler_strategy.h"

#include "base_context.h"

namespace Controller {
class GameController;
};

namespace Context {
class ShopContext: public BaseContext {
    friend class Controller::ShopEventHandlerStrategy;

private:
    void build_button(View::Button& button, const std::string& weapon_name,
                      Model::WeaponID weapon_id);
    void trigger_buttons(Shared<SDL_Event> event);

protected:
    Controller::ShopEventHandlerStrategy strategy;
    View::VerticalPane background;
    View::Label label;
    View::Button buy_ak47;
    View::Button buy_m3;
    View::Button buy_awp;

    void render(uint8_t) override;
    void dispatch_events() override;

public:
    explicit ShopContext(Weak<Controller::GameController> controller);

    ~ShopContext() override = default;
};
};  // namespace Context

#endif  // CLIENT_GAME_CONTEXT_SHOP_CONTEXT_H
