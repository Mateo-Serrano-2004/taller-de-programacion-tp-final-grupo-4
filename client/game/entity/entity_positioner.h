#ifndef CLIENT_GAME_ENTITY_ENTITY_POSITIONER_H
#define CLIENT_GAME_ENTITY_ENTITY_POSITIONER_H

namespace View {
class Pane;

class EntityPositioner {
public:
    EntityPositioner() = default;

    void size_pane_relatively_to_parent(Pane& pane, double portion_x, double portion_y);
    void place_pane_relatively_to_parent(Pane& pane, double portion_x, double portion_y);

    ~EntityPositioner() = default;
};
};

#endif // CLIENT_GAME_ENTITY_ENTITY_POSITIONER_H
