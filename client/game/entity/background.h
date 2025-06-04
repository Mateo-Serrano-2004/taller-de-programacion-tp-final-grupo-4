#ifndef CLIENT_GAME_ENTITY_BACKGROUND_H
#define CLIENT_GAME_ENTITY_BACKGROUND_H

#include "common/definitions.h"

#include "rect_entity.h"
#include "rendered.h"

namespace Controller {
class BaseController;
};

namespace View {
class Background: public Rendered, public RectEntity {
public:
    Background(short_id_t texture_id, Weak<Controller::BaseController> controller);

    void render() override;

    ~Background() override = default;
};
};

#endif //CLIENT_GAME_ENTITY_BACKGROUND_H
