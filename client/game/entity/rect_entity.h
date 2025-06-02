#ifndef CLIENT_GAME_ENTITY_RECT_ENTITY_H
#define CLIENT_GAME_ENTITY_RECT_ENTITY_H

#include "common/definitions.h"

#include "entity.h"

namespace View {
class RectEntity : public Entity {
protected:
    length_t width;
    length_t height;

    RectEntity(const RectEntity&) = delete;
    RectEntity& operator=(const RectEntity&) = delete;

public:
    RectEntity(coord_t x, coord_t y, length_t width, length_t height);
    RectEntity(coord_t x, coord_t y, length_t width, length_t height, Callback on_click);

    length_t get_width() const;
    length_t get_height() const;

    void set_width(length_t new_width);
    void set_height(length_t new_height);

    RectEntity(RectEntity&&) = default;
    RectEntity& operator=(RectEntity&&) = default;

    virtual ~RectEntity() = default;
};
};

#endif // CLIENT_GAME_ENTITY_RECT_ENTITY_H
