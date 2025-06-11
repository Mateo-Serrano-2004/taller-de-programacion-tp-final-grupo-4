#ifndef CLIENT_GAME_ENTITY_HORIZONTAL_PANE_H
#define CLIENT_GAME_ENTITY_HORIZONTAL_PANE_H

#include "common/definitions.h"

#include "smart_pane.h"
#include "gapped.h"

namespace Controller {
class BaseController;
};

namespace View {
class HorizontalPane: public SmartPane, public Gapped {
protected:
    void position_children() override;

public:
    HorizontalPane(Weak<Controller::BaseController> controller, int gap_x = 0);

    virtual ~HorizontalPane() override = default;
};
};

#endif // CLIENT_GAME_ENTITY_HORIZONTAL_PANE_H
