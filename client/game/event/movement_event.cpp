#include "movement_event.h"

Model::MovementEvent::MovementEvent(coord_t x, coord_t y):
        Model::Event(Model::EventType::MOVEMENT), direction(x, y) {}

Physics::Vector2D Model::MovementEvent::get_direction() const { return direction; }
