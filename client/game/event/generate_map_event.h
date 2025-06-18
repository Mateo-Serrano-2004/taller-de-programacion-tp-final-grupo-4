#ifndef CLIENT_GAME_EVENT_GENERATE_MAP_EVENT_H
#define CLIENT_GAME_EVENT_GENERATE_MAP_EVENT_H

#include "common/DTO/map_dto.h"

#include "event.h"

namespace Model {
class GenerateMapEvent: public Event {
protected:
    DTO::MapDTO dto;

public:
    explicit GenerateMapEvent(DTO::MapDTO&& dto);

    DTO::MapDTO get_map_dto();

    ~GenerateMapEvent() override = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_EVENT_GENERATE_MAP_EVENT_H
