#ifndef CLIENT_EVENT_BUY_WEAPON_EVENT_H
#define CLIENT_EVENT_BUY_WEAPON_EVENT_H

#include "common/DTO/event_dto.h"
#include "common/weapon_id.h"
#include "dto_handler/dto_creator_visitor.h"

#include "transfered_event.h"

namespace Model {
class BuyWeaponEvent: public TransferedEvent {
private:
    Model::WeaponID weapon_id;

public:
    explicit BuyWeaponEvent(Model::WeaponID weapon_id);

    Model::WeaponID get_weapon_id() const;

    DTO::EventDTO as_dto() override;

    ~BuyWeaponEvent() override = default;
};
}  // namespace Model

#endif  // CLIENT_EVENT_BUY_WEAPON_EVENT_H
