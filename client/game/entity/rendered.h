#ifndef CLIENT_GAME_ENTITY_RENDERED_H
#define CLIENT_GAME_ENTITY_RENDERED_H

#include "common/definitions.h"
#include "common/texture_id.h"

namespace SDL2pp {
class Window;
class Renderer;
};

namespace Model {
class AssetManager;
};

namespace Controller {
class BaseController;
};

namespace View {
class Rendered {
protected:
    Shared<SDL2pp::Window> window;
    Shared<SDL2pp::Renderer> renderer;
    Shared<Model::AssetManager> asset_manager;
    Model::TextureID texture_id;

public:
    Rendered(Model::TextureID texture_id, Weak<Controller::BaseController> controller);

    void set_new_texture_id(Model::TextureID new_texture_id);

    virtual void render() = 0;

    virtual ~Rendered() = default;
};
};

#endif // CLIENT_GAME_ENTITY_RENDERED_H
