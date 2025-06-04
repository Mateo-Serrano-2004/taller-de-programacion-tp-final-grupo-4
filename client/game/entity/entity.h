#ifndef CLIENT_GAME_ENTITY_ENTITY_H
#define CLIENT_GAME_ENTITY_ENTITY_H

#include <SDL2pp/Point.hh>

#include "common/definitions.h"
#include "common/model/vector_2d.h"

#include "render/render_context.h"

namespace View {
class Entity {
protected:
    SDL2pp::Point position;

public:
    Entity();
    Entity(coord_t x, coord_t y);
    Entity(const SDL2pp::Point& point);

    coord_t get_x() const;
    coord_t get_y() const;
    SDL2pp::Point get_position() const;

    void set_position(coord_t x, coord_t y);
    void set_position(const SDL2pp::Point& point);

    Entity(const Entity&) = default;
    Entity& operator=(const Entity&) = default;
    Entity(Entity&&) = default;
    Entity& operator=(Entity&&) = default;

    virtual ~Entity() = default;
};
};

#endif // CLIENT_GAME_ENTITY_ENTITY_H
