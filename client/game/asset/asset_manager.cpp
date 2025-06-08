#include "asset_manager.h"

#include <string>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Font.hh>
#include <SDL2pp/Color.hh>

Model::AssetManager::AssetManager(Shared<SDL2pp::Renderer> renderer)
: renderer(renderer),
  asset_generator(renderer) {}

void Model::AssetManager::load_texture(Model::TextureID id, const std::string& path) {
    textures.insert({id, make_shared<SDL2pp::Texture>(*renderer, path)});
}

void Model::AssetManager::load_texture(Model::TextureID id, Shared<SDL2pp::Texture> texture) {
    textures.insert({id, texture});
}

Shared<SDL2pp::Texture> Model::AssetManager::generate_background(
    uint8_t red,
    uint8_t green,
    uint8_t blue,
    uint8_t alpha
) {
    color_tuple color(red, green, blue, alpha);
    auto bg = backgrounds.find(color);
    if (bg != backgrounds.end()) return bg->second;
    auto new_bg = asset_generator.generate_plain_texture(SDL2pp::Color(red, green, blue, alpha));
    backgrounds.insert({color, new_bg});
    return new_bg;
}

Shared<SDL2pp::Texture> Model::AssetManager::generate_background(const SDL2pp::Color& color) {
    return generate_background(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
}

void Model::AssetManager::load_font(Model::FontID id, const std::string& path, int size) {
    fonts.insert({id, make_shared<SDL2pp::Font>(path, size)});
}

void Model::AssetManager::load_font(Model::FontID id, Shared<SDL2pp::Font> font) {
    fonts.insert({id, font});
}

Shared<SDL2pp::Texture> Model::AssetManager::get_texture(Model::TextureID id) {
    return textures.at(id);
}

Shared<SDL2pp::Font> Model::AssetManager::get_font(Model::FontID id) {
    return fonts.at(id);
}

Shared<SDL2pp::Texture> Model::AssetManager::apply_font_to_text(
    Model::FontID id,
    const std::string& text,
    const SDL2pp::Color& color
) {
    SDL_Color sdl_color {color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha()};
    return make_shared<SDL2pp::Texture>(*renderer, fonts.at(id)->RenderText_Blended(text, sdl_color));
}
