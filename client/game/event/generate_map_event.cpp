#include "generate_map_event.h"

#include <utility>

#include "common/event_type.h"

Model::GenerateMapEvent::GenerateMapEvent(DTO::MapDTO&& dto):
        Model::Event(Model::EventType::GENERATE_MAP), dto(std::move(dto)) {}

DTO::MapDTO Model::GenerateMapEvent::get_map_dto() { return dto; }
