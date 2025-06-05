#include "asset_generator.h"

#include <cmath>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Color.hh>
#include <SDL2pp/Point.hh>

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
