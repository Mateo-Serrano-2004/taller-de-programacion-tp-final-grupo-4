#ifndef CLIENT_GAME_EVENT_USE_WEAPON_EVENT_H
#define CLIENT_GAME_EVENT_USE_WEAPON_EVENT_H

#include "event.h"

namespace Model {
class UseWeaponEvent: public Event {
public:
    UseWeaponEvent();
    ~UseWeaponEvent() override = default;
};
};

#endif // CLIENT_GAME_EVENT_USE_WEAPON_EVENT_H
