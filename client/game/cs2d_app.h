#ifndef CLIENT_GAME_CS2D_APP_H
#define CLIENT_GAME_CS2D_APP_H

#include <string>

#include "common/definitions.h"

#include "application.h"

namespace Net {
class ClientProtocol;
};

namespace Controller {
class GameController;
};

namespace App {
class CS2DApp: public Application {
protected:
    CS2DApp(const CS2DApp&) = delete;
    CS2DApp& operator=(const CS2DApp&) = delete;
    CS2DApp(CS2DApp&&) = delete;
    CS2DApp& operator=(CS2DApp&&) = delete;

    Shared<Controller::GameController> set_up_graphics(Shared<Net::ClientProtocol> protocol);
    void set_up_contexts(Weak<Controller::GameController> game_controller);

public:
    explicit CS2DApp(Shared<Net::ClientProtocol> protocol);

    ~CS2DApp() override = default;
};
};  // namespace App

#endif  // CLIENT_GAME_CS2D_APP_H
