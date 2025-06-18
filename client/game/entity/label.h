#ifndef CLIENT_GAME_ENTITY_LABEL_H
#define CLIENT_GAME_ENTITY_LABEL_H

#include <cstdint>
#include <string>

#include <SDL2pp/Color.hh>

#include "common/definitions.h"
#include "interface/padded.h"

#include "pane.h"

namespace SDL2pp {
class Font;
class Texture;
};  // namespace SDL2pp

namespace Controller {
class BaseController;
};

namespace View {
class Label: public Pane, public Padded {
protected:
    std::string text;
    uint8_t font_size;
    SDL2pp::Color color;
    Shared<SDL2pp::Font> font;
    Shared<SDL2pp::Texture> text_texture;

public:
    explicit Label(Weak<Controller::BaseController> controller);

    std::string get_text() const;
    uint8_t get_font_size() const;
    SDL2pp::Color get_font_color() const;

    bool empty() const;

    void set_text(const std::string& new_text);
    void set_font_size(uint8_t new_font_size);
    void set_font_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

    void set_size(const SDL2pp::Point& new_size) override;
    void set_height(int new_height) override;
    void set_width(int new_width) override;

    void set_padding(int new_padding) override;

    void render() override;

    ~Label() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_ENTITY_LABEL_H
