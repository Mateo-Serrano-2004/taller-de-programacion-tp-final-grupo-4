#ifndef CLIENT_GAME_EVENT_STOP_USING_WEAPON_EVENT_H
#define CLIENT_GAME_EVENT_STOP_USING_WEAPON_EVENT_H

#include "event.h"

namespace Model {
class StopUsingWeaponEvent: public Event {
public:
    StopUsingWeaponEvent();
    ~StopUsingWeaponEvent() override = default;
};
};

#endif // CLIENT_GAME_EVENT_STOP_USING_WEAPON_EVENT_H
