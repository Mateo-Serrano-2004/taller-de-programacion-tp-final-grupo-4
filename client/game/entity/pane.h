#ifndef CLIENT_GAME_ENTITY_PANE_H
#define CLIENT_GAME_ENTITY_PANE_H

#include <list>

#include <SDL2pp/Optional.hh>
#include <SDL2pp/Point.hh>

#include "asset/texture_id.h"
#include "common/definitions.h"
#include "interface/rendered.h"
#include "interface/rotated.h"
#include "interface/textured.h"

namespace SDL2pp {
class Texture;
class Color;
};  // namespace SDL2pp

namespace Controller {
class BaseController;
};

namespace View {
class Pane: public Rendered, public Textured, public Rotated {
protected:
    bool position_set;
    bool size_set;

    std::list<Pane*> children;
    bool draw_background;
    Shared<SDL2pp::Texture> background;
    SDL2pp::Point position;
    SDL2pp::Point size;
    Pane* parent;

    void render_texture(Shared<SDL2pp::Texture> texture);

public:
    explicit Pane(Weak<Controller::BaseController> controller);

    bool get_draw_background() const;
    Shared<SDL2pp::Texture> get_background() const;
    SDL2pp::Point get_position() const;
    int get_x() const;
    int get_y() const;
    SDL2pp::Point get_size() const;
    int get_height() const;
    int get_width() const;
    SDL2pp::Point get_absolute_position() const;
    Pane* get_parent() const;

    void set_draw_background(bool new_draw_background);
    void set_background_color(const SDL2pp::Color& new_color);
    void set_background_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    void set_position(const SDL2pp::Point& new_position);
    void set_x(int new_x);
    void set_y(int new_y);
    virtual void set_width(int new_width);
    virtual void set_height(int new_height);
    virtual void set_size(const SDL2pp::Point& new_size);
    void set_parent(Pane* new_parent);

    virtual void add_child(Pane* new_child);
    virtual void clear_children();

    virtual void render() override;

    virtual ~Pane() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_ENTITY_PANE_H
