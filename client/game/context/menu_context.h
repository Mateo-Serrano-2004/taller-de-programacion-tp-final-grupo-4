#ifndef CLIENT_GAME_CONTEXT_MENU_CONTEXT_H
#define CLIENT_GAME_CONTEXT_MENU_CONTEXT_H

#include <cstdint>

#include "common/definitions.h"
#include "entity/button.h"
#include "entity/horizontal_pane.h"
#include "entity/label.h"
#include "entity/vertical_pane.h"
#include "event/event.h"
#include "handler/menu_event_handler_strategy.h"
#include "render/player_renderer.h"

#include "base_context.h"

namespace Controller {
class GameController;
class GameStateManager;
};  // namespace Controller

namespace Context {
class MenuContext: public BaseContext {
    friend class Controller::MenuEventHandlerStrategy;

private:
    void trigger_buttons(Shared<SDL_Event> event);

protected:
    Controller::MenuEventHandlerStrategy strategy;
    View::PlayerRenderer player_renderer;
    Shared<Controller::GameStateManager> game_state_manager;

    View::VerticalPane viewport;
    View::VerticalPane background;
    View::Label ask_to_leave_label;
    View::HorizontalPane buttons;
    View::Button return_game_button;
    View::Button exit_button;

    void render(uint8_t) override;
    void dispatch_events() override;

    void build_button(View::Button& button);

    MenuContext(const MenuContext&) = delete;
    MenuContext& operator=(const MenuContext&) = delete;

public:
    explicit MenuContext(Weak<Controller::GameController> controller);

    MenuContext(MenuContext&&) = default;
    MenuContext& operator=(MenuContext&&) = default;

    ~MenuContext() override = default;
};
};  // namespace Context

#endif  // CLIENT_GAME_CONTEXT_MENU_CONTEXT_H
