#ifndef CLIENT_GAME_HANDLER_MOVEMENT_HANDLER_H
#define CLIENT_GAME_HANDLER_MOVEMENT_HANDLER_H

#include <unordered_set>

#include <SDL2/SDL.h>

#include "game_handler.h"

namespace Controller {
class GameController;

class MovementHandler: public GameHandler {
private:
    inline static bool moving_horizontally = false;
    inline static bool moving_vertically = false;
    std::unordered_set<Uint32> handled_types;
    std::unordered_set<SDL_Keycode> handled_codes;

    void set_up_handled_types();

    void on_vertical_stop();
    void on_horizontal_stop();
    void on_vertical_movement(const SDL_Event& event);
    void on_horizontal_movement(const SDL_Event& event);
    void update_movement_state(const SDL_Event& event);

public:
    explicit MovementHandler(Weak<GameController> controller);

    void handle(const SDL_Event& event) override;
    bool can_handle(const SDL_Event& event) override;
    void stop();

    ~MovementHandler() override = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_HANDLER_MOVEMENT_HANDLER_H
