#include "asset_manager.h"

#include <memory>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/Chunk.hh>
#include <SDL2pp/Color.hh>
#include <SDL2pp/Font.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include "common/DTO/map_dto.h"
#include "controller/subsystem_manager.h"

Model::AssetManager::AssetManager(Controller::SubsystemManager* subsystem_manager,
                                  Shared<SDL2pp::Renderer> renderer, const DTO::ConfigDTO& config):
        subsystem_manager(subsystem_manager),
        renderer(renderer),
        config(config),
        cursor_manager(renderer),
        asset_generator(renderer, config),
        current_map(nullptr) {}

void Model::AssetManager::load_texture(Model::TextureID id, const std::string& path) {
    textures.insert({id, make_shared<SDL2pp::Texture>(*renderer, path)});
}

void Model::AssetManager::load_texture(Model::TextureID id, Shared<SDL2pp::Texture> texture) {
    textures.insert({id, texture});
}

void Model::AssetManager::load_animation(Model::AnimationID id,
                                         const Model::AnimationDetails& details) {
    animations.insert({id, details});
}

void Model::AssetManager::load_sound(Model::SoundID id, const std::string& path) {
    chunks.insert({id, make_shared<SDL2pp::Chunk>(asset_addresser.get_sound_path(path))});
}

void Model::AssetManager::load_cursor(CursorID id, const std::string& path,
                                      const SDL2pp::Rect& srect) {
    cursor_manager.load_cursor_texture(id, path, srect);
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

Shared<SDL2pp::Font> Model::AssetManager::generate_font(const std::string& name, uint8_t size) {
    font_tuple font(name, size);
    auto f = fonts.find(font);
    if (f != fonts.end())
        return f->second;
    auto new_f = asset_generator.generate_font(asset_addresser.get_font_path(name), size);
    fonts.insert({font, new_f});
    return new_f;
}

Shared<SDL2pp::Texture> Model::AssetManager::get_texture(Model::TextureID id) {
    return textures.at(id);
}

const Model::AnimationDetails& Model::AssetManager::get_animation(AnimationID id) {
    return animations.at(id);
}

Shared<SDL2pp::Chunk> Model::AssetManager::get_sound(SoundID id) { return chunks.at(id); }

SDL2pp::Mixer* Model::AssetManager::get_mixer() { return &(subsystem_manager->get_mixer()); }

Shared<SDL2pp::Texture> Model::AssetManager::apply_font_to_text(Shared<SDL2pp::Font> font,
                                                                const std::string& text,
                                                                const SDL2pp::Color& color) {
    SDL_Color sdl_color{color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha()};
    return make_shared<SDL2pp::Texture>(*renderer, font->RenderText_Blended(text, sdl_color));
}

void Model::AssetManager::set_cursor(CursorID id, const SDL2pp::Point& hotspot) {
    cursor_manager.apply_cursor(id, hotspot);
}
