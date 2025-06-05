#ifndef CLIENT_GAME_EVENT_PICK_SPRITE_EVENT_H
#define CLIENT_GAME_EVENT_PICK_SPRITE_EVENT_H

#include "common/texture_id.h"

#include "event.h"

namespace Model {
class PickSpriteEvent: public Event {
protected:
    TextureID sprite_id;

public:
    explicit PickSpriteEvent(TextureID sprite_id);

    TextureID get_sprite_id() const;

    ~PickSpriteEvent() override = default;
};
};

#endif // CLIENT_GAME_EVENT_PICK_SPRITE_EVENT_H
