#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "ui_main_window.h"
#include "scenes/lobby_scene.h"
#include "scenes/welcome_scene.h"
#include "scenes/game_creation_scene.h"
#include "scenes/join_game_scene.h"
#include "client/net/client_protocol.h"

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

protected:
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

private slots:
    void onPushButtonClicked();
    void receiveAvailableGames(const QStringList& partidas);

private:
    Ui::MainWindow *ui;
    LobbyScene* lobbyScene;
    WelcomeScene* welcomeScene;
    GameCreationScene *gameCreationScene;
    JoinGameScene* joinGameScene;
    Net::ClientProtocol* protocol = nullptr;
    void setUpWindow();
};
#endif // MAIN_WINDOW_H
