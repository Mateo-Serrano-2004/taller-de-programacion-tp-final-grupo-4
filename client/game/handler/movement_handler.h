#ifndef CLIENT_GAME_HANDLER_MOVEMENT_HANDLER_H
#define CLIENT_GAME_HANDLER_MOVEMENT_HANDLER_H

#include <unordered_set>

#include <SDL2/SDL.h>

#include "game_handler.h"

namespace Controller {
class GameController;

class MovementHandler: public GameHandler {
private:
    std::unordered_set<Uint32> handled_types;
    std::unordered_set<SDL_Keycode> handled_codes;
    bool moving_horizontally;
    bool moving_vertically;

    void set_up_handled_types();

    void on_vertical_stop();
    void on_horizontal_stop();
    void on_vertical_movement(SDL_Event& event);
    void on_horizontal_movement(SDL_Event& event);
    void update_movement_state(SDL_Event& event);

public:
    MovementHandler(Weak<GameController> controller);

    void handle(SDL_Event& event) override;
    bool can_handle(SDL_Event& event) override;
    void stop();

    ~MovementHandler() override = default;
};
};

#endif // CLIENT_GAME_HANDLER_MOVEMENT_HANDLER_H
