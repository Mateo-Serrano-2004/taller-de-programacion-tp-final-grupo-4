#include "stop_using_weapon_event.h"

#include "common/event_type.h"

Model::StopUsingWeaponEvent::StopUsingWeaponEvent()
: Model::Event(Model::EventType::STOP_USING_WEAPON) {}
