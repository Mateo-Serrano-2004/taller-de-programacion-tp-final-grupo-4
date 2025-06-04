#ifndef CLIENT_GAME_HANDLER_CALLBACK_H
#define CLIENT_GAME_HANDLER_CALLBACK_H

#include <functional>

#include "common/definitions.h"

namespace Controller {
class BaseController;

class Callback {
protected:
    Weak<BaseController> controller;
    std::function<void(Weak<Controller::BaseController>)> callback;

public:
    Callback(
        Weak<BaseController> controller
    );

    Callback(
        Weak<BaseController> controller,
        std::function<void(Weak<Controller::BaseController>)> callback
    );

    bool is_valid() const;

    void set_callback(std::function<void(Weak<Controller::BaseController>)> new_callback);

    void operator()() {
        if (callback) callback(controller);
    }

    virtual ~Callback() = default;
};
};

#endif // CLIENT_GAME_HANDLER_CALLBACK_H
