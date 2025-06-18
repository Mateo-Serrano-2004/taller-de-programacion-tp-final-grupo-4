#ifndef CLIENT_GAME_EVENT_PICK_ROLE_EVENT_H
#define CLIENT_GAME_EVENT_PICK_ROLE_EVENT_H

#include "common/DTO/event_dto.h"
#include "common/role_id.h"
#include "dto_handler/dto_creator_visitor.h"

#include "transfered_event.h"

namespace Model {
class PickRoleEvent: public TransferedEvent {
protected:
    RoleID role_id;

public:
    explicit PickRoleEvent(RoleID role_id);

    RoleID get_role_id() const;

    DTO::EventDTO as_dto() override;

    ~PickRoleEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_PICK_ROLE_EVENT_H
