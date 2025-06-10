#include "buy_weapon_event.h"

#include "common/event_type.h"

Model::BuyWeaponEvent::BuyWeaponEvent(Model::WeaponID weapon_id)
: Model::Event(Model::EventType::BUY_WEAPON), weapon_id(weapon_id) {}

Model::WeaponID Model::BuyWeaponEvent::get_weapon_id() const {
    return weapon_id;
}
