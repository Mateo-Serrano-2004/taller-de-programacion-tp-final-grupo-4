#ifndef CLIENT_GAME_HANDLER_HANDLER_STATE_H
#define CLIENT_GAME_HANDLER_HANDLER_STATE_H

namespace Model {
struct HandlerState {
public:
    bool moving_vertically;
    bool moving_horizontally;
    bool switching_weapon;
    bool is_shooting;
    bool is_defusing;

    HandlerState();
    ~HandlerState() = default;
};
};  // namespace Model

#endif  // CLIENT_GAME_HANDLER_HANDLER_STATE_H
