#ifndef CLIENT_GAME_EVENT_GENERATE_MAP_EVENT_H
#define CLIENT_GAME_EVENT_GENERATE_MAP_EVENT_H

#include "common/DTO/map_dto.h"

#include "event.h"

namespace Model {
class GenerateMapEvent: public Event {
protected:
    DTO::MapDTO dto;

public:
    GenerateMapEvent(DTO::MapDTO&& dto);

    DTO::MapDTO get_map_dto();

    ~GenerateMapEvent() override = default;
};
};

#endif // CLIENT_GAME_EVENT_GENERATE_MAP_EVENT_H
