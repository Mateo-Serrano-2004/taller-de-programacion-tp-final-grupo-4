#ifndef CLIENT_GAME_EVENT_SWITCH_WEAPON_EVENT_H
#define CLIENT_GAME_EVENT_SWITCH_WEAPON_EVENT_H

#include "common/DTO/event_dto.h"
#include "common/slot_id.h"
#include "dto_handler/dto_creator_visitor.h"

#include "transfered_event.h"

namespace Model {
class SwitchWeaponEvent: public TransferedEvent {
protected:
    SlotID slot_id;

public:
    explicit SwitchWeaponEvent(SlotID slot_id);

    SlotID get_slot_id() const;

    DTO::EventDTO as_dto() override;

    ~SwitchWeaponEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_SWITCH_WEAPON_EVENT_H
