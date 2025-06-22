#include "weapon_handler.h"

#include <SDL2/SDL.h>

#include "controller/game_controller.h"
#include "event/use_weapon_event.h"
#include "event/stop_using_weapon_event.h"
#include "event/switch_weapon_event.h"
#include "event/defuse_bomb_event.h"
#include "event/drop_weapon_event.h"
#include "event/stop_defusing_bomb_event.h"

void Controller::WeaponHandler::set_up_handled_types() {
    handled_types.insert(SDL_KEYDOWN);
    handled_types.insert(SDL_KEYUP);
    handled_types.insert(SDL_MOUSEBUTTONDOWN);
    handled_types.insert(SDL_MOUSEBUTTONUP);

    handled_codes.insert(SDLK_1);
    handled_codes.insert(SDLK_2);
    handled_codes.insert(SDLK_3);
    handled_codes.insert(SDLK_4);
    handled_codes.insert(SDLK_e);
    handled_codes.insert(SDLK_g);

    ids.insert({SDLK_1, Model::SlotID::PRIMARY_WEAPON});
    ids.insert({SDLK_2, Model::SlotID::SECONDARY_WEAPON});
    ids.insert({SDLK_3, Model::SlotID::KNIFE_SLOT});
    ids.insert({SDLK_4, Model::SlotID::BOMB_SLOT});
}

void Controller::WeaponHandler::handle_mouse(SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (!is_shooting) {
            controller.lock()->push_event(make_shared<Model::UseWeaponEvent>());
            is_shooting = true;
        }
    } else if (event.type == SDL_MOUSEBUTTONUP) {
        if (is_shooting) {
            controller.lock()->push_event(make_shared<Model::StopUsingWeaponEvent>());
            is_shooting = false;
        }
    }
}

void Controller::WeaponHandler::handle_switching(SDL_Event& event) {
    auto slot = ids.at(event.key.keysym.sym);
    if (event.type == SDL_KEYDOWN) {
        if (!is_switching) {
            controller.lock()->push_event(make_shared<Model::SwitchWeaponEvent>(slot));
            is_switching = true;
        }
    } else if (event.type == SDL_KEYUP) {
        is_switching = false;
    }
}

void Controller::WeaponHandler::handle_defusing(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        if (!is_defusing) {
            controller.lock()->push_event(make_shared<Model::DefuseBombEvent>());
            is_defusing = true;
        }
    } else if (event.type == SDL_KEYUP) {
        if (is_defusing) {
            controller.lock()->push_event(make_shared<Model::StopDefusingBombEvent>());
            is_defusing = false;
        }
    }
}

void Controller::WeaponHandler::handle_drop(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        if (!is_dropping) {
            controller.lock()->push_event(make_shared<Model::DropWeaponEvent>());
            is_dropping = true;
        }
    } else if (event.type == SDL_KEYUP) {
        is_dropping = false;
    }
}

void Controller::WeaponHandler::handle_key(SDL_Event& event) {
    if (event.key.keysym.sym == SDLK_e) {
        handle_defusing(event);
    } else if (event.key.keysym.sym == SDLK_g) {
        handle_drop(event);
    } else {
        handle_switching(event);
    }
}

Controller::WeaponHandler::WeaponHandler(Weak<GameController> controller)
: Controller::GameHandler(controller),
  is_shooting(false),
  is_switching(false),
  is_defusing(false),
  is_dropping(false) {
    set_up_handled_types();
}

void Controller::WeaponHandler::handle(SDL_Event& event) {
    if (can_handle(event)) {
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            handle_key(event);
        } else {
            handle_mouse(event);
        }
    }
}

bool Controller::WeaponHandler::can_handle(SDL_Event& event) {
    if (handled_types.find(event.type) == handled_types.end())
        return false;

    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        return handled_codes.find(event.key.keysym.sym) != handled_codes.end();
    }

    if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
        return event.button.button == SDL_BUTTON_LEFT;
    }

    return false;
}

void Controller::WeaponHandler::stop() {
    if (is_shooting) {
        controller.lock()->push_event(make_shared<Model::StopUsingWeaponEvent>());
        is_shooting = false;
    }
    is_switching = false;
    if (is_defusing) {
        controller.lock()->push_event(make_shared<Model::StopDefusingBombEvent>());
        is_defusing = false;
    }
}
