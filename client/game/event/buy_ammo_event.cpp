#include "buy_ammo_event.h"

#include "common/event_type.h"
#include "dto_handler/dto_creator_visitor.h"

Model::BuyAmmoEvent::BuyAmmoEvent(Model::SlotID slot_id):
        Model::TransferedEvent(Model::EventType::BUY_AMMO), slot_id(slot_id) {}

Model::SlotID Model::BuyAmmoEvent::get_slot_id() const { return slot_id; }

DTO::EventDTO Model::BuyAmmoEvent::as_dto() {
    return DTO::DTOCreatorVisitor::visit_buy_ammo_event(this);
}
