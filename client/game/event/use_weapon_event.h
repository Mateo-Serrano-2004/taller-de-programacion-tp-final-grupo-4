#ifndef CLIENT_GAME_EVENT_USE_WEAPON_EVENT_H
#define CLIENT_GAME_EVENT_USE_WEAPON_EVENT_H

#include "common/DTO/event_dto.h"
#include "dto_handler/dto_creator_visitor.h"

#include "transfered_event.h"

namespace Model {
class UseWeaponEvent: public TransferedEvent {
public:
    UseWeaponEvent();

    DTO::EventDTO as_dto() override;

    ~UseWeaponEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_USE_WEAPON_EVENT_H
