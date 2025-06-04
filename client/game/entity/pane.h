#ifndef CLIENT_GAME_ENTITY_PANE_H
#define CLIENT_GAME_ENTITY_PANE_H

#include <SDL2pp/Optional.hh>
#include <SDL2pp/Rect.hh>

#include "common/definitions.h"

#include "rendered.h"

namespace Controller {
class BaseController;
};

namespace View {
class Pane: public Rendered {
protected:
    Pane* parent;
    SDL2pp::Optional<SDL2pp::Rect> position;
    SDL2pp::Optional<SDL2pp::Rect> texture_slice;

    SDL2pp::Rect get_parent_position();
    SDL2pp::Rect get_displacement_within_parent();

public:
    Pane(
        short_id_t texture_id,
        Weak<Controller::BaseController> controller,
        Pane* parent
    );

    Pane(
        short_id_t texture_id,
        Weak<Controller::BaseController> controller
    );

    bool has_position() const;
    SDL2pp::Rect get_position() const;
    void set_position(const SDL2pp::Rect& new_position);
    void set_auto_fit();

    bool has_texture_slice() const;
    SDL2pp::Rect get_texture_slice() const;
    void set_texture_slice(const SDL2pp::Rect& new_slice);
    void set_full_texture();

    virtual void render() override;

    virtual ~Pane() override = default;
};
};

#endif // CLIENT_GAME_ENTITY_PANE_H
