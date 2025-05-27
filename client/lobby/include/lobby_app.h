#ifndef LOBBY_APP_H
#define LOBBY_APP_H

#include <QApplication>
#include "mainwindow.h"

class LobbyApp : public QApplication {
    Q_OBJECT

private:
    QApplication *app;
    MainWindow *mainWindow;
public:
    LobbyApp(int &argc, char **argv);
    int running();
} 
#endif // LOBBY_APP_H