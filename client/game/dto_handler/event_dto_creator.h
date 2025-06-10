#ifndef CLIENT_DTO_PARSER_EVENT_DTO_CREATOR_H
#define CLIENT_DTO_PARSER_EVENT_DTO_CREATOR_H

#include <utility>

#include "common/DTO/event_dto.h"
#include "common/definitions.h"
#include "event/event.h"


namespace DTO {
class EventDTOCreator {
private:
    Shared<Model::Event> event;

    EventDTO create_buy_weapon_event() const;
    EventDTO create_use_weapon_event() const;
    EventDTO create_stop_using_weapon_event() const;
    EventDTO create_pick_role_event() const;
    EventDTO create_request_maps_event() const;
    EventDTO create_request_games_list_event() const;
    EventDTO create_username_event() const;
    EventDTO create_quit_event() const;
    EventDTO create_new_match_event() const;
    EventDTO create_join_game_event() const;
    EventDTO create_movement_event() const;
    EventDTO create_stop_movement_event() const;
    EventDTO create_rotation_event() const;
    EventDTO create_switch_weapon_event() const;

public:
    explicit EventDTOCreator(Shared<Model::Event> event): event(std::move(event)) {}

    EventDTO to_dto() const;

    ~EventDTOCreator() = default;
};
};  // namespace DTO

#endif  // CLIENT_DTO_PARSER_EVENT_DTO_CREATOR_H
