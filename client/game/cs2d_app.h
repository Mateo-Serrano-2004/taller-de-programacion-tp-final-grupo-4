#ifndef CLIENT_GAME_CS2D_APP_H
#define CLIENT_GAME_CS2D_APP_H

#include "application.h"

namespace Net {
class ClientProtocol;
};

namespace App {
class CS2DApp: public Application {
protected:
    CS2DApp(const CS2DApp&) = delete;
    CS2DApp& operator=(const CS2DApp&) = delete;
    CS2DApp(CS2DApp&&) = delete;
    CS2DApp& operator=(CS2DApp&&) = delete;

public:
    CS2DApp(Net::ClientProtocol* protocol);

    ~CS2DApp() override = default;
};
};

#endif // CLIENT_GAME_CS2D_APP_H
