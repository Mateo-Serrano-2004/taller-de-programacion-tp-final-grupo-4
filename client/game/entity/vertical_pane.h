#ifndef CLIENT_GAME_ENTITY_VERTICAL_PANE_H
#define CLIENT_GAME_ENTITY_VERTICAL_PANE_H

#include "common/definitions.h"
#include "interface/gapped.h"

#include "smart_pane.h"

namespace Controller {
class BaseController;
};

namespace View {
class VerticalPane: public SmartPane, public Gapped {
protected:
    void position_children() override;

    void fit() override;

public:
    explicit VerticalPane(Weak<Controller::BaseController> controller, int gap_y = 0);

    virtual ~VerticalPane() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_ENTITY_VERTICAL_PANE_H
