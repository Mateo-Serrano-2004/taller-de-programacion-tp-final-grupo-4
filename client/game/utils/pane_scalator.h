#ifndef CLIENT_GAME_UTILS_PANE_SCALATOR_H
#define CLIENT_GAME_UTILS_PANE_SCALATOR_H

namespace View {
class Pane;
class PaneScalator {
public:
    static void scalate_height_with_aspect_ratio(Pane* pane, int new_height);
    static void scalate_width_with_aspect_ratio(Pane* pane, int new_width);
};
};  // namespace View

#endif  // CLIENT_GAME_UTILS_PANE_SCALATOR_H
