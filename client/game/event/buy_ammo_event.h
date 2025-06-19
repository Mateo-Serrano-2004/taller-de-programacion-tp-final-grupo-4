#ifndef CLIENT_EVENT_BUY_AMMO_EVENT_H
#define CLIENT_EVENT_BUY_AMMO_EVENT_H

#include "common/DTO/event_dto.h"
#include "common/slot_id.h"

#include "transfered_event.h"

namespace Model {
class BuyAmmoEvent: public TransferedEvent {
private:
    Model::SlotID slot_id;

public:
    explicit BuyAmmoEvent(Model::SlotID slot_id);

    Model::SlotID get_slot_id() const;

    DTO::EventDTO as_dto() override;

    ~BuyAmmoEvent() override = default;
};
}  // namespace Model

#endif  // CLIENT_EVENT_BUY_AMMO_EVENT_H
