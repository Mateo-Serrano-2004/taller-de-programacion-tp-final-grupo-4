#ifndef CLIENT_GAME_ENTITY_RENDERED_H
#define CLIENT_GAME_ENTITY_RENDERED_H

#include "common/definitions.h"

namespace SDL2pp {
class Window;
class Renderer;
};

namespace Model {
class TextureStorage;
};

namespace Controller {
class BaseController;
};

namespace View {
class Rendered {
protected:
    Shared<SDL2pp::Window> window;
    Shared<SDL2pp::Renderer> renderer;
    Shared<Model::TextureStorage> texture_storage;
    short_id_t texture_id;

public:
    Rendered(short_id_t texture_id, Weak<Controller::BaseController> controller);

    void set_new_texture_id(short_id_t new_texture_id);

    virtual void render() = 0;

    virtual ~Rendered() = default;
};
};

#endif // CLIENT_GAME_ENTITY_RENDERED_H
