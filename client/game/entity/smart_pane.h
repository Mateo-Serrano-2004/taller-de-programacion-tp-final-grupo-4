#ifndef CLIENT_GAME_ENTITY_SMART_PANE_H
#define CLIENT_GAME_ENTITY_SMART_PANE_H

#include <vector>

#include "common/definitions.h"

#include "pane.h"

namespace Controller {
class BaseController;
};

namespace View {
class SmartPane: public Pane {
protected:
    std::vector<Pane*> children;

    virtual void position_children() = 0;

public:
    SmartPane(Weak<Controller::BaseController> controller);

    void add_child(Pane* new_child);

    virtual void render() override;

    virtual ~SmartPane() override = default;
};
};

#endif // CLIENT_GAME_ENTITY_SMART_PANE_H
