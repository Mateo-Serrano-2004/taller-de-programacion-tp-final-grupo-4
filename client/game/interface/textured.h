#ifndef CLIENT_GAME_ENTITY_TEXTURED_H
#define CLIENT_GAME_ENTITY_TEXTURED_H

#include <SDL2pp/Optional.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Texture.hh>

#include "asset/texture_id.h"
#include "common/definitions.h"

namespace Model {
class AssetManager;
};

namespace Controller {
class BaseController;
};

namespace View {
class Textured {
protected:
    bool draw_texture;
    Shared<SDL2pp::Texture> texture;
    SDL2pp::Optional<SDL2pp::Rect> texture_slice;
    Shared<Model::AssetManager> asset_manager;

public:
    explicit Textured(Weak<Controller::BaseController> controller);

    bool is_texture_drawn() const;
    SDL2pp::Optional<SDL2pp::Rect> get_texture_slice() const;

    void set_draw_texture(bool new_draw_texture);
    void set_texture(Shared<SDL2pp::Texture> new_texture);
    void set_texture(Model::TextureID new_texture_id);
    void set_texture_slice(const SDL2pp::Rect& new_texture_slice);
    void reset_texture_slice();

    virtual ~Textured() = default;
};
};  // namespace View

#endif  // CLIENT_GAME_ENTITY_TEXTURED_H
