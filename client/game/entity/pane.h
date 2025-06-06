#ifndef CLIENT_GAME_ENTITY_PANE_H
#define CLIENT_GAME_ENTITY_PANE_H

#include <SDL2pp/Optional.hh>
#include <SDL2pp/Rect.hh>

#include "common/definitions.h"
#include "common/texture_id.h"

#include "asset/background_id.h"

#include "rendered.h"

namespace SDL2pp {
class Texture;
};

namespace Controller {
class BaseController;
};

namespace View {
class Pane: public Rendered {
protected:
    Model::BackgroundID background_id;
    Shared<SDL2pp::Texture> background;
    SDL2pp::Optional<SDL2pp::Rect> position;
    Pane* parent;

public:
    Pane(
        Weak<Controller::BaseController> controller,
        Pane* parent = nullptr
    );

    Model::BackgroundID get_background_id() const;
    bool has_position() const;
    SDL2pp::Rect get_position() const;
    SDL2pp::Rect get_absolute_position() const;
    SDL2pp::Rect get_parent_position() const;

    void set_background(Model::BackgroundID new_background_id);
    void set_position(const SDL2pp::Rect& new_position);
    void set_auto_fit();
    void set_full_texture();
    void set_texture_slice_to_match_position();
    void set_parent(Pane* new_parent);

    virtual void render() override;

    virtual ~Pane() override = default;
};
};

#endif // CLIENT_GAME_ENTITY_PANE_H
