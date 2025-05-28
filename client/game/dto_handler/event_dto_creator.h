#ifndef CLIENT_DTO_PARSER_EVENT_DTO_CREATOR_H
#define CLIENT_DTO_PARSER_EVENT_DTO_CREATOR_H

#include "common/definitions.h"
#include "common/DTO/event_dto.h"

#include "common/event/event.h"


namespace DTO {
    class EventDTOCreator {
    private:
        Shared<Model::Event> event;

        EventDTO create_username_event() const;
        EventDTO create_quit_event() const;
        EventDTO create_new_match_event() const;
        EventDTO create_join_game_event() const;
        EventDTO create_movement_event() const;
        EventDTO create_rotation_event() const;

    public:
        EventDTOCreator(Shared<Model::Event> event)
        : event(std::move(event)) {}

        EventDTO to_dto() const;

        ~EventDTOCreator() = default;
    };
};

#endif // CLIENT_DTO_PARSER_EVENT_DTO_CREATOR_H
