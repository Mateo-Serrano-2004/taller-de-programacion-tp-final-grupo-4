#ifndef CLIENT_LOBBY_LOBBY_APP_H
#define CLIENT_LOBBY_LOBBY_APP_H

#include <QApplication>

#include "client/app.h"

#include "main_window.h"

namespace App {
class LobbyApp: public App {
private:
    QApplication app;
    MainWindow w;

public:
    LobbyApp(int argc, char* argv[]);

    void run() override;

    ~LobbyApp() override = default;
};
};  // namespace App

#endif  // CLIENT_LOBBY_LOBBY_APP_H
