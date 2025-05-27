#ifndef CLIENT_DTO_PARSER_EVENT_DTO_CREATOR_H
#define CLIENT_DTO_PARSER_EVENT_DTO_CREATOR_H

#include "common/definitions.h"
#include "common/DTO/event_dto.h"

#include "event/event.h"


namespace DTO {
    class EventDTOCreator {
    private:
        Shared<Event> event;

        EventDTO create_movement_event();
        EventDTO create_rotation_event();

    public:
        EventDTOCreator(Shared<Event> event)
        : event(std::move(event)) {}

        EventDTO create();

        ~EventDTOCreator() = default;
    };
};

#endif // CLIENT_DTO_PARSER_EVENT_DTO_CREATOR_H
