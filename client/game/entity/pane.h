#ifndef CLIENT_GAME_ENTITY_PANE_H
#define CLIENT_GAME_ENTITY_PANE_H

#include <list>

#include <SDL2pp/Optional.hh>
#include <SDL2pp/Point.hh>

#include "common/definitions.h"

#include "asset/texture_id.h"

#include "rendered.h"
#include "scalable.h"
#include "aligner.h"

namespace SDL2pp {
class Texture;
class Color;
};

namespace Controller {
class BaseController;
};

namespace View {
class Pane: public Rendered, public Scalable {
protected:
    std::list<Pane*> children;
    bool draw_background;
    Shared<SDL2pp::Texture> background;
    SDL2pp::Point position;
    Pane* parent;

    void render_texture(Shared<SDL2pp::Texture> texture);

public:
    Pane(Weak<Controller::BaseController> controller);

    bool get_draw_background() const;
    Shared<SDL2pp::Texture> get_background() const;
    SDL2pp::Point get_position() const;
    int get_x() const;
    int get_y() const;
    SDL2pp::Point get_absolute_position() const;
    Pane* get_parent() const;

    void set_draw_background(bool new_draw_background);
    void set_background_color(const SDL2pp::Color& new_color);
    void set_background_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    void set_position(const SDL2pp::Point& new_position);
    void set_x(int new_x);
    void set_y(int new_y);
    void set_width(int new_width);
    void set_height(int new_height);
    void set_size(const SDL2pp::Point& new_size);
    void set_parent(Pane* new_parent);

    void add_child(Pane* new_child);
    void clear_children();

    void scalate();

    virtual void render() override;

    virtual ~Pane() override = default;
};
};

#endif // CLIENT_GAME_ENTITY_PANE_H
