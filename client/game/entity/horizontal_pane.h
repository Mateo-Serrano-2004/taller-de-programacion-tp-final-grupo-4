#ifndef CLIENT_GAME_ENTITY_HORIZONTAL_PANE_H
#define CLIENT_GAME_ENTITY_HORIZONTAL_PANE_H

#include <vector>

#include "common/definitions.h"

#include "pane.h"

namespace Controller {
class BaseController;
};

namespace View {
class HorizontalPane: public Pane {
protected:
    std::vector<Pane*> children;
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
