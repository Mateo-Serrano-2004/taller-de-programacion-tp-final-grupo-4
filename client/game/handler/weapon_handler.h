#ifndef CLIENT_GAME_HANDLER_WEAPON_HANDLER_H
#define CLIENT_GAME_HANDLER_WEAPON_HANDLER_H

#include <unordered_set>
#include <unordered_map>
#include <SDL2/SDL.h>

#include "common/definitions.h"
#include "common/slot_id.h"

#include "game_handler.h"

namespace Controller {
class GameController;
class WeaponHandler: public GameHandler {
private:
    std::unordered_set<Uint32> handled_types;
    std::unordered_set<SDL_Keycode> handled_codes;
    std::unordered_map<SDL_Keycode, Model::SlotID> ids;
    bool is_shooting;
    bool is_switching;
    bool is_defusing;
    bool is_dropping;

    void set_up_handled_types();

    void handle_mouse(SDL_Event& event);

    void handle_switching(SDL_Event& event);
    void handle_defusing(SDL_Event& event);
    void handle_drop(SDL_Event& event);
    void handle_key(SDL_Event& event);

public:
    WeaponHandler(Weak<GameController> controller);

    void handle(SDL_Event& event) override;
    bool can_handle(SDL_Event& event) override;
    void stop();

    ~WeaponHandler() override = default;
};
};

#endif // CLIENT_GAME_HANDLER_WEAPON_HANDLER_H
