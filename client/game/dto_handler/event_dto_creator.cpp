#include "event_dto_creator.h"

#include "event/event_types.h"

#include <cstdint>
#include <vector>
#include <arpa/inet.h>

DTO::EventDTO DTO::EventDTOCreator::create_movement_event() {
    auto movement_event = std::static_pointer_cast<Model::MovementEvent>(event);
    DTO::EventDTO event_dto;

    uint8_t event_dto_size = 2;
    std::vector<char> data;
    data.push_back(static_cast<char>(Model::EventType::MOVEMENT));
    data.push_back(static_cast<char>(0x00));
    data.push_back(static_cast<char>(movement_event->get_x_direction()));
    data.push_back(static_cast<char>(movement_event->get_x_direction()));

    event_dto.size = event_dto_size;
    event_dto.data = std::move(data);

    return event_dto;
}

DTO::EventDTO DTO::EventDTOCreator::create_rotation_event() {
    auto rotation_event = std::static_pointer_cast<Model::RotationEvent>(event);
    DTO::EventDTO event_dto;

    uint8_t event_dto_size = 2;
    std::vector<char> data;

    int16_t angle = rotation_event->get_angle_in_degrees();
    char* ptr = reinterpret_cast<char*>(&hotns(angle));

    data.push_back(static_cast<char>(Model::EventType::ROTATION));
    data.push_back(static_cast<char>(0x01));
    data.push_back(ptr[0]);
    data.push_back(ptr[1]);

    event_dto.size = event_dto_size;
    event_dto.data = std::move(data);

    return event_dto;
}

DTO::EventDTO DTO::EventDTOCreator::create() {
    Model::EventType type = event->get_type();
    switch (type) {
        case Model::EventType::MOVEMENT:
            return create_movement_event();
        case Model::EventType::ROTATION:
            return create_rotation_event();
        default:
            throw std::runtime_error("Unknown event type");
    }
}
