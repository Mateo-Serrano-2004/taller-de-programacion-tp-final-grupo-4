#ifndef CLIENT_GAME_UTILS_LINE_H
#define CLIENT_GAME_UTILS_LINE_H

#include "common/definitions.h"
#include "entity/horizontal_pane.h"

namespace Controller {
class GameController;
};

namespace View {
class Line: public HorizontalPane {
public:
    View::HorizontalPane first_item;
    View::HorizontalPane second_item;

    Line(Weak<Controller::GameController> controller);

    ~Line() = default;
};
};

#endif // CLIENT_GAME_UTILS_LINE_H
