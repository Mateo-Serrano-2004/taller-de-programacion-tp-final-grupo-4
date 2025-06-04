#ifndef CLIENT_GAME_ENTITY_RECT_ENTITY_H
#define CLIENT_GAME_ENTITY_RECT_ENTITY_H

#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>

#include "common/definitions.h"

#include "entity.h"

namespace View {
class RectEntity : public Entity {
protected:
    SDL2pp::Point size;

public:
    RectEntity();
    RectEntity(coord_t x, coord_t y, coord_t width, coord_t height);
    RectEntity(const SDL2pp::Point& point, const SDL2pp::Point& size);
    RectEntity(const SDL2pp::Rect& rect);

    coord_t get_width() const;
    coord_t get_height() const;
    SDL2pp::Point get_size() const;
    SDL2pp::Rect get_rect() const;

    void set_width(coord_t new_width);
    void set_height(coord_t new_height);
    void set_size(const SDL2pp::Point& new_size);
    void set_rect(const SDL2pp::Rect& new_rect);

    RectEntity(const RectEntity&) = default;
    RectEntity& operator=(const RectEntity&) = default;
    RectEntity(RectEntity&&) = default;
    RectEntity& operator=(RectEntity&&) = default;

    virtual ~RectEntity() = default;
};
};

#endif // CLIENT_GAME_ENTITY_RECT_ENTITY_H
