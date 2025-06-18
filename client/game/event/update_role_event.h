#ifndef CLIENT_GAME_EVENT_UPDATE_ROLE_EVENT_H
#define CLIENT_GAME_EVENT_UPDATE_ROLE_EVENT_H

#include "common/team.h"

#include "event.h"

namespace Model {
class UpdateRoleEvent: public Event {
protected:
    TeamID id;

public:
    explicit UpdateRoleEvent(TeamID id);

    TeamID get_team() const;

    ~UpdateRoleEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_UPDATE_ROLE_EVENT_H
