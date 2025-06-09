#ifndef CLIENT_GAME_ENTITY_VERTICAL_PANE_H
#define CLIENT_GAME_ENTITY_VERTICAL_PANE_H

#include <vector>

#include "common/definitions.h"

#include "smart_pane.h"

namespace Controller {
class BaseController;
};

namespace View {
class VerticalPane: public SmartPane {
protected:
    int gap;

    void position_children() override;

public:
    VerticalPane(Weak<Controller::BaseController> controller, int gap = 0);

    int get_gap() const;
    void set_gap(int new_gap);

    virtual ~VerticalPane() override = default;
};
};

#endif // CLIENT_GAME_ENTITY_VERTICAL_PANE_H
