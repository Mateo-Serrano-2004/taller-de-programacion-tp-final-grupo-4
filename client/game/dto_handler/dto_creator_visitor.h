#ifndef CLIENT_GAME_DTO_HANDLER_DTO_CREATOR_VISITOR_H
#define CLIENT_GAME_DTO_HANDLER_DTO_CREATOR_VISITOR_H

#include "common/DTO/event_dto.h"

namespace Model {
class BuyAmmoEvent;
class BuyWeaponEvent;
class CreateGameEvent;
class JoinGameEvent;
class MovementEvent;
class PickRoleEvent;
class RotationEvent;
class StopMovementEvent;
class SwitchWeaponEvent;
class UsernameEvent;
};  // namespace Model

namespace DTO {
class DTOCreatorVisitor {
public:
    static EventDTO visit_buy_ammo_event(Model::BuyAmmoEvent* event);
    static EventDTO visit_buy_weapon_event(Model::BuyWeaponEvent* event);
    static EventDTO visit_create_game_event(Model::CreateGameEvent* event);
    static EventDTO visit_defuse_bomb_event();
    static EventDTO visit_drop_weapon_event();
    static EventDTO visit_join_game_event(Model::JoinGameEvent* event);
    static EventDTO visit_leave_event();
    static EventDTO visit_movement_event(Model::MovementEvent* event);
    static EventDTO visit_pick_role_event(Model::PickRoleEvent* event);
    static EventDTO visit_quit_event();
    static EventDTO visit_reload_event();
    static EventDTO visit_request_games_list_event();
    static EventDTO visit_request_maps_event();
    static EventDTO visit_rotation_event(Model::RotationEvent* event);
    static EventDTO visit_stop_defusing_bomb_event();
    static EventDTO visit_stop_movement_event(Model::StopMovementEvent* event);
    static EventDTO visit_stop_using_weapon_event();
    static EventDTO visit_switch_weapon_event(Model::SwitchWeaponEvent* event);
    static EventDTO visit_use_weapon_event();
    static EventDTO visit_username_event(Model::UsernameEvent* event);
};
};  // namespace DTO

#endif  // CLIENT_GAME_DTO_HANDLER_DTO_CREATOR_VISITOR_H
