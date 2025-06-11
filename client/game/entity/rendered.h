#ifndef CLIENT_GAME_ENTITY_RENDERED_H
#define CLIENT_GAME_ENTITY_RENDERED_H

#include <SDL2pp/Optional.hh>
#include <SDL2pp/Rect.hh>

#include "common/definitions.h"

#include "asset/texture_id.h"

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
    angle_t angle;
    Shared<SDL2pp::Texture> texture;
    SDL2pp::Optional<SDL2pp::Rect> texture_slice;
    Shared<SDL2pp::Window> window;
    Shared<SDL2pp::Renderer> renderer;
    Shared<Model::AssetManager> asset_manager;

public:
    Rendered(Weak<Controller::BaseController> controller);
    
    bool is_texture_drawn() const;
    bool has_texture_slice() const;
    SDL2pp::Rect get_texture_slice() const;
    angle_t get_angle() const;

    void set_draw_texture(bool new_draw_texture);
    void set_texture(Shared<SDL2pp::Texture> new_texture);
    void set_texture(Model::TextureID new_texture_id);
    void set_texture_slice(const SDL2pp::Rect& new_texture_slice);
    void set_angle(angle_t new_angle);

    virtual void render() = 0;

    virtual ~Rendered() = default;
};
};

#endif // CLIENT_GAME_ENTITY_RENDERED_H
