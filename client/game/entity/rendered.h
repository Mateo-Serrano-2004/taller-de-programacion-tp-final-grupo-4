#ifndef CLIENT_GAME_ENTITY_RENDERED_H
#define CLIENT_GAME_ENTITY_RENDERED_H

#include <SDL2pp/Optional.hh>
#include <SDL2pp/Rect.hh>

#include "common/definitions.h"
#include "common/texture_id.h"

namespace SDL2pp {
class Window;
class Renderer;
class Texture;
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
    bool draw_texture;
    Model::TextureID texture_id;
    Shared<SDL2pp::Texture> texture;
    SDL2pp::Optional<SDL2pp::Rect> texture_slice;
    Shared<SDL2pp::Window> window;
    Shared<SDL2pp::Renderer> renderer;
    Shared<Model::AssetManager> asset_manager;

public:
    Rendered(Weak<Controller::BaseController> controller);
    
    bool is_texture_drawn() const;
    Model::TextureID get_texture_id() const;
    bool has_texture_slice() const;
    SDL2pp::Rect get_texture_slice() const;

    void set_draw_texture(bool new_draw_texture);
    void set_texture(Model::TextureID new_texture_id);
    void set_texture_slice(const SDL2pp::Rect& new_texture_slice);

    virtual void render() = 0;

    virtual ~Rendered() = default;
};
};

#endif // CLIENT_GAME_ENTITY_RENDERED_H
