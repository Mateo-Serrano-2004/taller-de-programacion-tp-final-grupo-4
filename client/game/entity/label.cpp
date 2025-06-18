#include "label.h"

#include <string>

#include <SDL2pp/Color.hh>
#include <SDL2pp/Font.hh>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>

#include "asset/asset_manager.h"
#include "controller/base_controller.h"

View::Label::Label(Weak<Controller::BaseController> controller):
        View::Pane(controller),
        View::Padded(),
        text(""),
        font_size(12),
        color(255, 255, 255, 255),
        font(nullptr),
        text_texture(nullptr) {
    font = asset_manager->generate_font("liberationsans", font_size);
}

std::string View::Label::get_text() const { return text; }

uint8_t View::Label::get_font_size() const { return font_size; }

SDL2pp::Color View::Label::get_font_color() const { return color; }

bool View::Label::empty() const { return text_texture == nullptr; }

void View::Label::set_text(const std::string& new_text) {
    text = new_text;
    if (!text.empty()) {
        text_texture = asset_manager->apply_font_to_text(font, text, color);
        set_width(text_texture->GetWidth());
        set_height(text_texture->GetHeight());
    } else {
        text_texture = nullptr;
        set_width(0);
        set_height(0);
    }
}

void View::Label::set_font_size(uint8_t new_font_size) {
    font_size = new_font_size;
    font = asset_manager->generate_font("liberationsans", font_size);
    if (!text.empty()) {
        text_texture = asset_manager->apply_font_to_text(font, text, color);
        set_width(text_texture->GetWidth());
        set_height(text_texture->GetHeight());
    }
}

void View::Label::set_font_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    color = SDL2pp::Color(red, green, blue, alpha);
    if (!text.empty()) {
        text_texture = asset_manager->apply_font_to_text(font, text, color);
    }
}

void View::Label::set_size(const SDL2pp::Point& new_size) {
    size = new_size;
    size.SetX(size.GetX() + (2 * padding));
    size.SetY(size.GetY() + (2 * padding));
}

void View::Label::set_height(int new_height) { size.SetY(new_height + (2 * padding)); }

void View::Label::set_width(int new_width) { size.SetX(new_width + (2 * padding)); }

void View::Label::set_padding(int new_padding) {
    padding = new_padding;
    size.SetX(size.GetX() + (2 * padding));
    size.SetY(size.GetY() + (2 * padding));
}

void View::Label::render() {
    View::Pane::render();
    if (!empty()) {
        SDL2pp::Point absolute_position = get_absolute_position();
        renderer->Copy(
                *text_texture, SDL2pp::NullOpt,
                SDL2pp::Point(
                        absolute_position.GetX() + (get_width() - text_texture->GetWidth()) / 2,
                        absolute_position.GetY() + (get_height() - text_texture->GetHeight()) / 2));
    }
}
