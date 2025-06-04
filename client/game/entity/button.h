#ifndef CLIENT_GAME_ENTITY_BUTTON_H
#define CLIENT_GAME_ENTITY_BUTTON_H

#include "common/definitions.h"

#include "rendered.h"
#include "rect_entity.h"

namespace SDL2pp {
class Rect;
};

namespace Controller {
class BaseController;
};

namespace View {
class Button: public Rendered, public RectEntity {
public:
    Button(
        const SDL2pp::Rect& rect,
        short_id_t texture_id,
        Weak<Controller::BaseController> controller
    );

    void render() override;

    ~Button() override = default;
};
};

#endif // CLIENT_GAME_ENTITY_BUTTON_H
