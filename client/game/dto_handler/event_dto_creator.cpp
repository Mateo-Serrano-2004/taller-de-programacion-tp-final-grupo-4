#include "event_dto_creator.h"

#include "common/event_type.h"
#include "event/username_event.h"
#include "event/movement_event.h"
#include "event/stop_movement_event.h"
#include "event/rotation_event.h"
#include "event/create_game_event.h"
#include "event/request_maps_event.h"
#include "event/quit_event.h"

#include <cstdint>
#include <vector>
#include <arpa/inet.h>

DTO::EventDTO DTO::EventDTOCreator::create_request_maps_event() const {
    DTO::EventDTO event_dto;
    std::vector<char> data;
    data.push_back(static_cast<char>(Model::EventType::REQUEST_MAPS));

    event_dto.size = 1;
    event_dto.data = std::move(data);

    return event_dto;
}

DTO::EventDTO DTO::EventDTOCreator::create_request_games_event() const {
    DTO::EventDTO event_dto;
    std::vector<char> data;
    data.push_back(static_cast<char>(Model::EventType::REQUEST_GAMES));

    event_dto.size = 1;
    event_dto.data = std::move(data);

    return event_dto;
}

DTO::EventDTO DTO::EventDTOCreator::create_username_event() const {
    auto username_event = std::static_pointer_cast<Model::UsernameEvent>(event);
    DTO::EventDTO event_dto;
    std::string username = username_event->get_username();
    uint8_t username_size = static_cast<uint8_t>(username.size());

    std::vector<char> data;
    data.push_back(static_cast<char>(Model::EventType::USERNAME));
    data.push_back(username_size);
    for (char& c : username) data.push_back(c);

    event_dto.size = username_size + 2;
    event_dto.data = std::move(data);

    return event_dto;
}

DTO::EventDTO DTO::EventDTOCreator::create_quit_event() const {
    DTO::EventDTO event_dto;

    uint8_t event_dto_size = 1;
    std::vector<char> data;
    data.push_back(static_cast<char>(0x20));

    event_dto.size = event_dto_size;
    event_dto.data = std::move(data);

    return event_dto;
}

DTO::EventDTO DTO::EventDTOCreator::create_new_match_event() const {
    auto create_game_event = std::static_pointer_cast<Model::CreateGameEvent>(event);
    DTO::EventDTO event_dto;
    std::string party_name = create_game_event->get_party_name();
    uint8_t party_name_size = static_cast<uint8_t>(party_name.size());
    std::string map_name = create_game_event->get_map_name();
    uint8_t map_name_size = static_cast<uint8_t>(map_name.size());

    std::vector<char> data;
    data.push_back(static_cast<char>(Model::EventType::CREATE_GAME));
    data.push_back(party_name_size);
    data.push_back(map_name_size);
    for (char& c : party_name) data.push_back(c);
    for (char& c : map_name) data.push_back(c);

    event_dto.size = party_name_size + map_name_size + 3;
    event_dto.data = std::move(data);

    return event_dto;
}

DTO::EventDTO DTO::EventDTOCreator::create_join_game_event() const {
    DTO::EventDTO event_dto;

    uint8_t event_dto_size = 2;
    std::vector<char> data;
    data.push_back(static_cast<char>(0x0C));
    data.push_back(static_cast<char>(0));

    event_dto.size = event_dto_size;
    event_dto.data = std::move(data);

    return event_dto;
}

DTO::EventDTO DTO::EventDTOCreator::create_movement_event() const {
    auto movement_event = std::static_pointer_cast<Model::MovementEvent>(event);
    DTO::EventDTO event_dto;

    uint8_t event_dto_size = 3;
    std::vector<char> data;
    data.push_back(static_cast<char>(Model::EventType::MOVEMENT));
    data.push_back(static_cast<char>(movement_event->get_x_direction()));
    data.push_back(static_cast<char>(movement_event->get_x_direction()));

    event_dto.size = event_dto_size;
    event_dto.data = std::move(data);

    return event_dto;
}

DTO::EventDTO DTO::EventDTOCreator::create_stop_movement_event() const {
    auto movement_event = std::static_pointer_cast<Model::StopMovementEvent>(event);
    DTO::EventDTO event_dto;

    uint8_t event_dto_size = 2;
    std::vector<char> data;
    data.push_back(static_cast<char>(Model::EventType::STOP_MOVEMENT));
    data.push_back(static_cast<char>(movement_event->is_horizontal_movement()));

    event_dto.size = event_dto_size;
    event_dto.data = std::move(data);

    return event_dto;
}

DTO::EventDTO DTO::EventDTOCreator::create_rotation_event() const {
    auto rotation_event = std::static_pointer_cast<Model::RotationEvent>(event);
    DTO::EventDTO event_dto;

    uint8_t event_dto_size = 3;
    std::vector<char> data;

    int16_t angle = htons(rotation_event->get_angle_in_degrees());
    char* ptr = reinterpret_cast<char*>(&angle);

    data.push_back(static_cast<char>(0x01));
    data.push_back(ptr[0]);
    data.push_back(ptr[1]);

    event_dto.size = event_dto_size;
    event_dto.data = std::move(data);

    return event_dto;
}

DTO::EventDTO DTO::EventDTOCreator::to_dto() const {
    Model::EventType type = event->get_type();
    switch (type) {
        case Model::EventType::MOVEMENT:
            return create_movement_event();
        case Model::EventType::STOP_MOVEMENT:
            return create_stop_movement_event();
        case Model::EventType::ROTATION:
            return create_rotation_event();
        case Model::EventType::CREATE_GAME:
            return create_new_match_event();
        case Model::EventType::QUIT:
            return create_quit_event();
        case Model::EventType::JOIN_GAME:
            return create_join_game_event();
        case Model::EventType::USERNAME:
            return create_username_event();
        case Model::EventType::REQUEST_MAPS:
            return create_request_maps_event();
        case Model::EventType::REQUEST_GAMES:
            return create_request_games_event();
        default:
            throw std::runtime_error("Unknown event type");
    }
}
