#ifndef CLIENT_GAME_HANDLER_WEAPON_HANDLER_H
#define CLIENT_GAME_HANDLER_WEAPON_HANDLER_H

#include <unordered_map>
#include <unordered_set>

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
    bool is_buying_ammo;
    bool is_reloading;

    void set_up_handled_types();

    void handle_mouse(const SDL_Event& event);

    void handle_switching(const SDL_Event& event);
    void handle_buy_ammo(const SDL_Event& event);
    void handle_reload(const SDL_Event& event);
    void handle_defusing(const SDL_Event& event);
    void handle_drop(const SDL_Event& event);
    void handle_key(const SDL_Event& event);

public:
    explicit WeaponHandler(Weak<GameController> controller);

    void handle(const SDL_Event& event) override;
    bool can_handle(const SDL_Event& event) override;
    void stop();

    ~WeaponHandler() override = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_HANDLER_WEAPON_HANDLER_H
