#ifndef CLIENT_GAME_CONTEXT_END_OF_GAME_CONTEXT_H
#define CLIENT_GAME_CONTEXT_END_OF_GAME_CONTEXT_H

#include <cstdint>

#include <SDL2/SDL.h>

#include "common/definitions.h"

#include "base_context.h"

#include "entity/horizontal_pane.h"
#include "entity/label.h"

namespace Controller {
class BaseController;
}

namespace Context {
class EndOfGameContext: public BaseContext {
protected:
    SDL_Event placeholder;
    View::HorizontalPane background;
    View::Label label;

    void render(uint8_t) override;
    void dispatch_events() override;

public:
    EndOfGameContext(Weak<Controller::BaseController> controller);
    ~EndOfGameContext() override = default;
};
};

#endif // CLIENT_GAME_CONTEXT_END_OF_GAME_CONTEXT_H
