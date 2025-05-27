#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "lobby_scene.h"
#include "welcome_scene.h"
#include "game_creation_scene.h"
#include "join_game_scene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LobbyScene* lobbyScene;
    WelcomeScene* welcomeScene;
    GameCreationScene *gameCreationScene;
    JoinGameScene* joinGameScene;
    void setUpWindow();
    void receiveAvailableGames(const QStringList& partidas);
    void onPushButtonClicked();
};
#endif // MAIN_WINDOW_H
