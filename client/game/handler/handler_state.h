#ifndef CLIENT_GAME_HANDLER_HANDLER_STATE_H
#define CLIENT_GAME_HANDLER_HANDLER_STATE_H

namespace Controller {
    class SDLEventHandler;
};

namespace Model {
    class HandlerState {
    friend class Controller::SDLEventHandler;

    private:
        bool moving_vertically;
        bool moving_horizontally;

    public:
        HandlerState();

        ~HandlerState() = default;
    };
};

#endif // CLIENT_GAME_HANDLER_HANDLER_STATE_H
