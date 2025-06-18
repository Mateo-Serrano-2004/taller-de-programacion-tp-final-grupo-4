#ifndef CLIENT_GAME_EVENT_STOP_USING_WEAPON_EVENT_H
#define CLIENT_GAME_EVENT_STOP_USING_WEAPON_EVENT_H

#include "common/DTO/event_dto.h"
#include "dto_handler/dto_creator_visitor.h"

#include "transfered_event.h"

namespace Model {
class StopUsingWeaponEvent: public TransferedEvent {
public:
    StopUsingWeaponEvent();

    DTO::EventDTO as_dto() override;

    ~StopUsingWeaponEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_STOP_USING_WEAPON_EVENT_H
