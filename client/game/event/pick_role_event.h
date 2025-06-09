#ifndef CLIENT_GAME_EVENT_PICK_ROLE_EVENT_H
#define CLIENT_GAME_EVENT_PICK_ROLE_EVENT_H

#include "common/role_id.h"

#include "event.h"

namespace Model {
class PickRoleEvent: public Event {
protected:
    RoleID role_id;

public:
    explicit PickRoleEvent(RoleID role_id);

    RoleID get_role_id() const;

    ~PickRoleEvent() override = default;
};
};

#endif // CLIENT_GAME_EVENT_PICK_ROLE_EVENT_H
