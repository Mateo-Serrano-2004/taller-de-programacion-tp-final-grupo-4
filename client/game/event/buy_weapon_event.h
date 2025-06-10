#ifndef CLIENT_EVENT_BUY_WEAPON_EVENT_H
#define CLIENT_EVENT_BUY_WEAPON_EVENT_H

#include "common/weapon_id.h"

#include "event.h"

namespace Model {
class BuyWeaponEvent: public Event {
private:
    Model::WeaponID weapon_id;

public:
    BuyWeaponEvent(Model::WeaponID weapon_id);

    Model::WeaponID get_weapon_id() const;

    ~BuyWeaponEvent() override = default;
};
}  // namespace Model

#endif  // CLIENT_EVENT_BUY_WEAPON_EVENT_H
