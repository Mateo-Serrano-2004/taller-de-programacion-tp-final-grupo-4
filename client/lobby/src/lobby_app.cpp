#include "lobby_app.h"

LobbyApp::LobbyApp(int& argc, char** argv, Net::ClientProtocol& protocol)
    : app(argc, argv), mainWindow(protocol){

    mainWindow.show();
}

int LobbyApp::run() {
    return app.exec();
}