#include "lobby_app.h"

App::LobbyApp::LobbyApp(int argc, char* argv[]): app(argc, argv) { run(); }

void App::LobbyApp::run() {
    w.show();
    app.exec();
}
