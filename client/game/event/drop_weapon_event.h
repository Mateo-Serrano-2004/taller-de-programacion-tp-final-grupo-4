#ifndef CLIENT_GAME_EVENT_DROP_WEAPON_EVENT_H
#define CLIENT_GAME_EVENT_DROP_WEAPON_EVENT_H

#include "common/DTO/event_dto.h"

#include "transfered_event.h"

namespace Model {
class DropWeaponEvent: public TransferedEvent {
public:
    DropWeaponEvent();

    DTO::EventDTO as_dto() override;

    ~DropWeaponEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_DROP_WEAPON_EVENT_H
