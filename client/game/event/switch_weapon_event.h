#ifndef CLIENT_GAME_EVENT_SWITCH_WEAPON_EVENT_H
#define CLIENT_GAME_EVENT_SWITCH_WEAPON_EVENT_H

#include "common/slot_id.h"

#include "event.h"

namespace Model {
class SwitchWeaponEvent: public Event {
protected:
    SlotID slot_id;

public:
    SwitchWeaponEvent(SlotID slot_id);

    SlotID get_slot_id() const;

    ~SwitchWeaponEvent() override = default;
};
};

#endif // CLIENT_GAME_EVENT_SWITCH_WEAPON_EVENT_H
