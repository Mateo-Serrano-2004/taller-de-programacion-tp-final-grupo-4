#include "dto_creator_visitor.h"

#include <string>

#include <arpa/inet.h>

#include "common/definitions.h"
#include "event/events.h"

DTO::EventDTO DTO::DTOCreatorVisitor::visit_buy_ammo_event(Model::BuyAmmoEvent* event) {
    DTO::EventDTO event_dto;

    event_dto.data.push_back(static_cast<char>(Model::EventType::BUY_AMMO));
    event_dto.data.push_back(static_cast<char>(event->get_slot_id()));

    event_dto.size = 2;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_buy_weapon_event(Model::BuyWeaponEvent* event) {
    DTO::EventDTO event_dto;

    event_dto.data.push_back(static_cast<char>(Model::EventType::BUY_WEAPON));
    event_dto.data.push_back(static_cast<char>(event->get_weapon_id()));

    event_dto.size = 2;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_create_game_event(Model::CreateGameEvent* event) {
    DTO::EventDTO event_dto;

    std::string party_name = event->get_party_name();
    uint8_t party_name_size = static_cast<uint8_t>(party_name.size());
    std::string map_name = event->get_map_name();
    uint8_t map_name_size = static_cast<uint8_t>(map_name.size());

    event_dto.data.push_back(static_cast<char>(Model::EventType::CREATE_GAME));
    event_dto.data.push_back(party_name_size);
    event_dto.data.push_back(map_name_size);
    event_dto.data.insert(event_dto.data.end(), party_name.begin(), party_name.end());
    event_dto.data.insert(event_dto.data.end(), map_name.begin(), map_name.end());

    event_dto.size = party_name_size + map_name_size + 3;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_defuse_bomb_event() {
    DTO::EventDTO event_dto;

    event_dto.data.push_back(static_cast<char>(Model::EventType::DEFUSE_BOMB));

    event_dto.size = 1;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_drop_weapon_event() {
    DTO::EventDTO event_dto;

    event_dto.data.push_back(static_cast<char>(Model::EventType::DROP_WEAPON));

    event_dto.size = 1;

    return event_dto;
}


DTO::EventDTO DTO::DTOCreatorVisitor::visit_join_game_event(Model::JoinGameEvent* event) {
    DTO::EventDTO event_dto;

    event_dto.data.push_back(static_cast<char>(Model::EventType::JOIN_GAME));
    event_dto.data.push_back(static_cast<char>(event->get_game_id()));

    event_dto.size = 2;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_leave_event() {
    DTO::EventDTO event_dto;

    event_dto.data.push_back(static_cast<char>(Model::EventType::LEAVE_GAME));

    event_dto.size = 1;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_movement_event(Model::MovementEvent* event) {
    DTO::EventDTO event_dto;

    event_dto.data.push_back(static_cast<char>(Model::EventType::MOVEMENT));

    auto direction = event->get_direction();
    event_dto.data.push_back(static_cast<char>(direction.get_x()));
    event_dto.data.push_back(static_cast<char>(direction.get_y()));

    event_dto.size = 3;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_pick_role_event(Model::PickRoleEvent* event) {
    DTO::EventDTO event_dto;

    event_dto.data.push_back(static_cast<char>(Model::EventType::PICK_ROLE));
    event_dto.data.push_back(static_cast<char>(event->get_role_id()));

    event_dto.size = 2;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_quit_event() {
    DTO::EventDTO event_dto;

    event_dto.data.push_back(static_cast<char>(Model::EventType::QUIT));

    event_dto.size = 1;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_reload_event() {
    DTO::EventDTO event_dto;

    event_dto.data.push_back(static_cast<char>(Model::EventType::RELOAD_WEAPON));

    event_dto.size = 1;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_request_games_list_event() {
    DTO::EventDTO event_dto;

    event_dto.data.push_back(static_cast<char>(Model::EventType::REQUEST_GAMES_LIST));

    event_dto.size = 1;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_request_maps_event() {
    DTO::EventDTO event_dto;

    event_dto.data.push_back(static_cast<char>(Model::EventType::REQUEST_MAPS));

    event_dto.size = 1;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_rotation_event(Model::RotationEvent* event) {
    DTO::EventDTO event_dto;

    angle_t angle = htons(event->get_angle_in_degrees());
    char* ptr = reinterpret_cast<char*>(&angle);

    event_dto.data.push_back(static_cast<char>(Model::EventType::ROTATION));
    event_dto.data.push_back(ptr[0]);
    event_dto.data.push_back(ptr[1]);

    event_dto.size = 3;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_stop_defusing_bomb_event() {
    DTO::EventDTO event_dto;

    event_dto.data.push_back(static_cast<char>(Model::EventType::STOP_DEFUSING_BOMB));

    event_dto.size = 1;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_stop_movement_event(Model::StopMovementEvent* event) {
    DTO::EventDTO event_dto;

    event_dto.data.push_back(static_cast<char>(Model::EventType::STOP_MOVEMENT));
    event_dto.data.push_back(static_cast<char>(event->is_horizontal_movement()));

    event_dto.size = 2;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_stop_using_weapon_event() {
    DTO::EventDTO event_dto;

    event_dto.data.push_back(static_cast<char>(Model::EventType::STOP_USING_WEAPON));

    event_dto.size = 1;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_switch_weapon_event(Model::SwitchWeaponEvent* event) {
    DTO::EventDTO event_dto;

    event_dto.data.push_back(static_cast<char>(Model::EventType::SWITCH_WEAPON));
    event_dto.data.push_back(static_cast<char>(event->get_slot_id()));

    event_dto.size = 2;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_use_weapon_event() {
    DTO::EventDTO event_dto;

    event_dto.data.push_back(static_cast<char>(Model::EventType::USE_WEAPON));

    event_dto.size = 1;

    return event_dto;
}

DTO::EventDTO DTO::DTOCreatorVisitor::visit_username_event(Model::UsernameEvent* event) {
    DTO::EventDTO event_dto;

    std::string username = event->get_username();
    uint8_t username_size = static_cast<uint8_t>(username.size());

    event_dto.data.push_back(static_cast<char>(Model::EventType::USERNAME));
    event_dto.data.push_back(username_size);
    event_dto.data.insert(event_dto.data.end(), username.begin(), username.end());

    event_dto.size = username_size + 2;

    return event_dto;
}
