#include "lobby_app.h"

#include "main_window.h"

#include <QApplication>

App::LobbyApp::LobbyApp(int argc, char* argv[])
: app(argc, argv) {
    run();
}

void App::LobbyApp::run() {
    w.show();
    app.exec();
}
