#ifndef CLIENT_GAME_ENTITY_HORIZONTAL_PANE_H
#define CLIENT_GAME_ENTITY_HORIZONTAL_PANE_H

#include <vector>

#include <SDL2pp/Rect.hh>

#include "common/definitions.h"

#include "pane.h"
#include "entity_positioner.h"

namespace Controller {
class BaseController;
};

namespace View {
class HorizontalPane: public Pane {
protected:
    EntityPositioner positioner;
    std::vector<Pane*> children;
    std::vector<SDL2pp::Rect> children_positions;
    int gap;

    void position_children();

public:
    HorizontalPane(Weak<Controller::BaseController> controller, int gap = 0);

    void set_gap(int new_gap);
    void add_child(Pane* new_child);

    int get_gap() const;

    virtual void render() override;

    virtual ~HorizontalPane() override = default;
};
};

#endif // CLIENT_GAME_ENTITY_HORIZONTAL_PANE_H
