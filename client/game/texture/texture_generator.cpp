#include "texture_generator.h"

#include <cmath>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Color.hh>

void View::TextureGenerator::draw_disk(int half_size, int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                renderer->DrawPoint(half_size + x, half_size + y);
            }
        }
    }
}

void View::TextureGenerator::draw_triangle(int half_size, int angle) {
    for (int i = 0; i < half_size; i++) {
        renderer->DrawLine(
            half_size - (i / std::tan((90 - angle) * M_PI / 180.0)),
            half_size - i,
            half_size + (i / std::tan((90 - angle) * M_PI / 180.0)),
            half_size - i);
    }
}

View::TextureGenerator::TextureGenerator(
    Shared<SDL2pp::Renderer> renderer
): renderer(renderer) {}

SDL2pp::Texture View::TextureGenerator::draw_field_of_view() {
    SDL_Rect bounds;
    if (SDL_GetDisplayBounds(0, &bounds) != 0) {
        throw std::runtime_error(std::string(SDL_GetError()));
    }

    // The size of the fov must be enough to cover
    // the whole screen even when rotated
    int max_fov_size = std::ceil(
        std::sqrt(
            (bounds.w * bounds.w) + (bounds.h * bounds.h)
        ) / 2.0
    );


    SDL2pp::Texture fov_texture(
        *renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        max_fov_size, // should be 2 * max_fov_size, but in debug mode screen is 640 x 480
        max_fov_size
    );
    // Allow blend
    fov_texture.SetBlendMode(SDL_BLENDMODE_BLEND);

    // Set blend for the current target
    renderer->SetTarget(fov_texture);
    renderer->SetDrawBlendMode(SDL_BLENDMODE_BLEND);

    SDL2pp::Color color = renderer->GetDrawColor(); // To restore it later
    renderer->SetDrawColor(0, 0, 0, 128); // Semi-transparent black
    renderer->Clear();
    renderer->SetDrawBlendMode(SDL_BLENDMODE_NONE); // Override the black transparency
    renderer->SetDrawColor(0, 0, 0, 0); // Transparent
    draw_disk(max_fov_size / 2, 30);
    draw_triangle(max_fov_size / 2, 30); // 30deg

    // Restore
    renderer->SetDrawColor(color);
    renderer->SetDrawBlendMode(SDL_BLENDMODE_BLEND);
    renderer->SetTarget();

    return fov_texture;
}
