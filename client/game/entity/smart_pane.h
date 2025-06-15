#ifndef CLIENT_GAME_ENTITY_SMART_PANE_H
#define CLIENT_GAME_ENTITY_SMART_PANE_H

#include <vector>

#include "common/definitions.h"

#include "interface/aligner.h"

#include "pane.h"

namespace Controller {
class BaseController;
};

namespace View {
class SmartPane: public Pane, public Aligner {
protected:
    virtual void position_children();

public:
    SmartPane(Weak<Controller::BaseController> controller);

    virtual void render() override;

    virtual ~SmartPane() override = default;
};
};

#endif // CLIENT_GAME_ENTITY_SMART_PANE_H
