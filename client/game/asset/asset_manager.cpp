#include "asset_manager.h"

#include <memory>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/Color.hh>
#include <SDL2pp/Font.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include "common/DTO/map_dto.h"

Model::AssetManager::AssetManager(Shared<SDL2pp::Renderer> renderer, const DTO::ConfigDTO& config):
        renderer(renderer),
        config(config),
        asset_generator(renderer, config),
        current_map(nullptr) {}

void Model::AssetManager::load_texture(Model::TextureID id, const std::string& path) {
    textures.insert({id, make_shared<SDL2pp::Texture>(*renderer, path)});
}

void Model::AssetManager::load_texture(Model::TextureID id, Shared<SDL2pp::Texture> texture) {
    textures.insert({id, texture});
}

void Model::AssetManager::load_animation(AnimationID id, const Model::AnimationDetails& details) {
    animations.insert({id, details});
}

Shared<SDL2pp::Texture> Model::AssetManager::generate_background(uint8_t red, uint8_t green,
                                                                 uint8_t blue, uint8_t alpha) {
    color_tuple color(red, green, blue, alpha);
    auto bg = backgrounds.find(color);
    if (bg != backgrounds.end())
        return bg->second;
    auto new_bg = asset_generator.generate_plain_texture(SDL2pp::Color(red, green, blue, alpha));
    backgrounds.insert({color, new_bg});
    return new_bg;
}

Shared<SDL2pp::Texture> Model::AssetManager::generate_background(const SDL2pp::Color& color) {
    return generate_background(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
}

Shared<SDL2pp::Texture> Model::AssetManager::generate_map(const DTO::MapDTO& map_dto) {
    current_map = asset_generator.generate_map(map_dto);
    return current_map;
}

Shared<SDL2pp::Texture> Model::AssetManager::get_texture(Model::TextureID id) {
    return textures.at(id);
}

const Model::AnimationDetails& Model::AssetManager::get_animation(AnimationID id) {
    return animations.at(id);
}

Shared<SDL2pp::Texture> Model::AssetManager::apply_font_to_text(uint8_t size,
                                                                const std::string& text,
                                                                const SDL2pp::Color& color) {
    SDL_Color sdl_color{color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha()};

    // To solve the issue of fonts destroying incorrectly when saved
    Shared<SDL2pp::Font> font = asset_generator.generate_font(
        asset_addresser.get_font_path("liberationsans"),
        size
    );
    return make_shared<SDL2pp::Texture>(*renderer, font->RenderText_Blended(text, sdl_color));
}
