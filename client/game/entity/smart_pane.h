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
    bool fit_to_children;

    virtual void position_children();

    virtual void fit();

public:
    explicit SmartPane(Weak<Controller::BaseController> controller);

    void set_fit_to_children(bool new_fit);

    void add_child(Pane* new_child) override;
    void clear_children() override;

    virtual void render() override;

    virtual ~SmartPane() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_ENTITY_SMART_PANE_H
