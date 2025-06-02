#ifndef CLIENT_GAME_ENTITY_ENTITY_H
#define CLIENT_GAME_ENTITY_ENTITY_H

#include <functional>

#include "common/definitions.h"
#include "common/model/vector_2d.h"

#include "render/render_context.h"

namespace Context {
class BaseContext;
};

namespace View {
class Entity {
protected:
    Physics::Vector2D position;
    Callback on_click;

    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

public:
    Entity(coord_t x, coord_t y);
    Entity(coord_t x, coord_t y, Callback on_click);

    Physics::Vector2D get_position() const;
    void set_position(coord_t x, coord_t y);

    void set_callback(Callback new_callback);

    void trigger_callback();

    virtual void render(RenderContext& render_context) = 0;

    Entity(Entity&&) = default;
    Entity& operator=(Entity&&) = default;

    virtual ~Entity() = default;
};
};

#endif // CLIENT_GAME_ENTITY_ENTITY_H
