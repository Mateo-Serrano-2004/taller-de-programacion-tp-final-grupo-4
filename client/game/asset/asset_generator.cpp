#include "asset_generator.h"

#include <cmath>
#include <string>
#include <unordered_map>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Font.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Color.hh>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>

#include "common/asset_addresser.h"
#include "common/DTO/map_dto.h"

SDL_Rect View::AssetGenerator::get_bounds() {
    SDL_Rect bounds;
    if (SDL_GetDisplayBounds(0, &bounds) != 0) {
        throw std::runtime_error(std::string(SDL_GetError()));
    }
    return bounds;
}

void View::AssetGenerator::draw_disk(int half_size, int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                renderer->DrawPoint(half_size + x, half_size + y);
            }
        }
    }
}

void View::AssetGenerator::draw_triangle(int half_size, int angle) {
    for (int i = 0; i < half_size; i++) {
        renderer->DrawLine(
            half_size - (i / std::tan((90 - angle) * M_PI / 180.0)),
            half_size - i,
            half_size + (i / std::tan((90 - angle) * M_PI / 180.0)),
            half_size - i);
    }
}

std::unordered_map<std::string, Shared<SDL2pp::Texture>> View::AssetGenerator::load_tiles(const DTO::MapDTO& map_dto) {
    Model::AssetAddresser addresser;
    std::unordered_map<std::string, Shared<SDL2pp::Texture>> tiles;

    for (const auto& row: map_dto.map) {
        for (const auto& col: row) {
            if (col.empty() || tiles.contains(col)) continue;
            tiles.insert({
                col,
                make_shared<SDL2pp::Texture>(
                    *renderer,
                    addresser.get_tile_path(col)
                )
            });
        }
    }
    return tiles;
}

void View::AssetGenerator::insert_tiles(
    Shared<SDL2pp::Texture> texture,
    const DTO::MapDTO& map_dto,
    std::unordered_map<std::string, Shared<SDL2pp::Texture>>& tiles
) {
    renderer->SetTarget(*texture);
    for (size_t i = 0; i < map_dto.count_of_rows; i++) {
        for (size_t j = 0; j < map_dto.count_of_columns; j++) {
            if (map_dto.map[i][j].empty()) continue;
            renderer->Copy(
                *(tiles.find(map_dto.map[i][j])->second),
                SDL2pp::NullOpt,
                SDL2pp::Rect(j * 32, i * 32, 32, 32)
            );
        }
    }
    renderer->SetTarget();
}

View::AssetGenerator::AssetGenerator(
    Shared<SDL2pp::Renderer> renderer
): renderer(renderer) {}

Shared<SDL2pp::Texture> View::AssetGenerator::generate_fov() {
    SDL_Rect bounds = get_bounds();

    // The size of the fov must be enough to cover
    // the whole screen even when rotated
    int max_fov_size = std::ceil(
        std::sqrt(
            (bounds.w * bounds.w) + (bounds.h * bounds.h)
        ) / 2.0
    );

    auto fov_texture = make_shared<SDL2pp::Texture>(
        *renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        2 * max_fov_size,
        2 * max_fov_size
    );

    // Allow blend
    fov_texture->SetBlendMode(SDL_BLENDMODE_BLEND);

    SDL2pp::Color color = renderer->GetDrawColor();
    SDL_BlendMode blend_mode = renderer->GetDrawBlendMode();

    // Set blend for the current target
    renderer->SetTarget(*fov_texture);
    renderer->SetDrawBlendMode(SDL_BLENDMODE_BLEND);
    renderer->SetDrawColor(0, 0, 0, 128); // Semi-transparent black

    renderer->Clear();

    renderer->SetDrawBlendMode(SDL_BLENDMODE_NONE); // Override the black transparency
    renderer->SetDrawColor(0, 0, 0, 0); // Transparent

    draw_disk(max_fov_size, 30);
    draw_triangle(max_fov_size, 30); // 30deg

    // Restore
    renderer->SetDrawColor(color);
    renderer->SetDrawBlendMode(blend_mode);
    renderer->SetTarget();

    return fov_texture;
}

Shared<SDL2pp::Texture> View::AssetGenerator::generate_plain_texture(
    const SDL2pp::Point& size,
    const SDL2pp::Color& color
) {
    auto texture = make_shared<SDL2pp::Texture>(
        *renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        size.GetX(),
        size.GetY()
    );

    SDL2pp::Color prev_color = renderer->GetDrawColor();
    SDL_BlendMode blend_mode = renderer->GetDrawBlendMode();

    renderer->SetTarget(*texture);
    renderer->SetDrawColor(color);
    renderer->Clear();

    renderer->SetDrawColor(prev_color);
    renderer->SetDrawBlendMode(blend_mode);
    renderer->SetTarget();

    return texture;
}

Shared<SDL2pp::Texture> View::AssetGenerator::generate_plain_texture(const SDL2pp::Color& color) {
    SDL_Rect bounds = get_bounds();
    return generate_plain_texture(SDL2pp::Point(bounds.w, bounds.h), color);
}

Shared<SDL2pp::Texture> View::AssetGenerator::generate_map(const DTO::MapDTO& map_dto) {
    size_t cols = static_cast<size_t>(map_dto.count_of_columns);
    size_t rows = static_cast<size_t>(map_dto.count_of_rows);
    size_t tile_size = 32;
    auto map_texture = make_shared<SDL2pp::Texture>(
        *renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        cols * tile_size,
        rows * tile_size
    );

    auto tiles = load_tiles(map_dto);
    insert_tiles(map_texture, map_dto, tiles);

    return map_texture;
}

Shared<SDL2pp::Font> View::AssetGenerator::generate_font(
    const std::string& path,
    uint8_t size
) {
    return make_shared<SDL2pp::Font>(path, size);
}
