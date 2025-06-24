#ifndef CLIENT_GAME_UTILS_STAT_LINE_H
#define CLIENT_GAME_UTILS_STAT_LINE_H

#include <cstdint>
#include <string>

#include "common/definitions.h"
#include "entity/horizontal_pane.h"
#include "entity/label.h"
#include "entity/pane.h"
#include "entity/vertical_pane.h"

namespace Controller {
class GameController;
};

namespace View {
class StatLine: public VerticalPane {
public:
    HorizontalPane line;
    HorizontalPane player_name_pane;
    Label player_name;
    HorizontalPane kills_pane;
    Label kills;
    HorizontalPane deaths_pane;
    Label deaths;
    Pane separator;

    explicit StatLine(Weak<Controller::GameController> controller);

    void set_name(const std::string& name);
    void set_kills(const std::string& kills_text);
    void set_deaths(const std::string& deaths_text);

    void set_all_texts_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    void set_all_fonts_size(uint8_t size);
    void set_line_height(uint8_t size);

    ~StatLine() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_UTILS_STAT_LINE_H
