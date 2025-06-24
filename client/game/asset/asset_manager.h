#ifndef CLIENT_GAME_ASSET_ASSET_MANAGER_H
#define CLIENT_GAME_ASSET_ASSET_MANAGER_H

#include <map>
#include <string>
#include <utility>

#include "animation/animation_details.h"
#include "asset/sound_id.h"
#include "asset/texture_id.h"
#include "common/DTO/config_dto.h"
#include "common/asset_addresser.h"

#include "animation_id.h"
#include "asset_generator.h"
#include "cursor_id.h"
#include "cursor_manager.h"
#include "font_id.h"
#include "texture_id.h"

namespace SDL2pp {
class Renderer;
class Texture;
class Font;
class Color;
class Chunk;
class Mixer;
class Rect;
class Point;
};  // namespace SDL2pp

namespace Controller {
class SubsystemManager;
};

namespace DTO {
struct MapDTO;
};

namespace Model {
class AssetManager {
private:
    AssetAddresser asset_addresser;
    Controller::SubsystemManager* subsystem_manager;
    Shared<SDL2pp::Renderer> renderer;
    DTO::ConfigDTO config;
    Model::CursorManager cursor_manager;
    View::AssetGenerator asset_generator;
    std::map<TextureID, Shared<SDL2pp::Texture>> textures;
    std::map<AnimationID, Model::AnimationDetails> animations;
    std::map<color_tuple, Shared<SDL2pp::Texture>> backgrounds;
    std::map<font_tuple, Shared<SDL2pp::Font>> fonts;
    std::map<SoundID, Shared<SDL2pp::Chunk>> chunks;
    Shared<SDL2pp::Texture> current_map;

public:
    AssetManager(Controller::SubsystemManager* subsystem_manager, Shared<SDL2pp::Renderer> renderer,
                 const DTO::ConfigDTO& config);

    void load_texture(TextureID id, const std::string& path);
    void load_texture(TextureID id, Shared<SDL2pp::Texture> texture);
    void load_animation(AnimationID id, const Model::AnimationDetails& details);
    void load_sound(SoundID id, const std::string& path);
    void load_cursor(CursorID id, const std::string& path, const SDL2pp::Rect& srect);

    Shared<SDL2pp::Texture> generate_background(uint8_t red, uint8_t green, uint8_t blue,
                                                uint8_t alpha);
    Shared<SDL2pp::Texture> generate_background(const SDL2pp::Color& color);

    Shared<SDL2pp::Font> generate_font(const std::string& name, uint8_t size);

    Shared<SDL2pp::Texture> generate_map(const DTO::MapDTO& map_dto);

    Shared<SDL2pp::Texture> get_texture(TextureID id);
    const Model::AnimationDetails& get_animation(AnimationID id);
    Shared<SDL2pp::Chunk> get_sound(SoundID id);
    SDL2pp::Mixer* get_mixer();

    Shared<SDL2pp::Texture> apply_font_to_text(Shared<SDL2pp::Font> font, const std::string& text,
                                               const SDL2pp::Color& color);
    void set_cursor(CursorID id, const SDL2pp::Point& hotspot);

    ~AssetManager() = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_ASSET_ASSET_MANAGER_H
