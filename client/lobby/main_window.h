#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QAudioOutput>
#include <QDir>

#include "client/net/client_protocol.h"
#include "common/definitions.h"
#include "scenes/game_creation_scene.h"
#include "scenes/join_game_scene.h"
#include "scenes/lobby_scene.h"
#include "scenes/welcome_scene.h"

#include "ui_main_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

protected:
    void resizeEvent(QResizeEvent* event) override;
    void showEvent(QShowEvent* event) override;

private slots:
    void onPushButtonClicked();
    void receiveAvailableMaps(const QStringList& maps);

private:
    Ui::MainWindow* ui;
    WelcomeScene* welcomeScene = nullptr;
    LobbyScene* lobbyScene = nullptr;
    GameCreationScene* gameCreationScene = nullptr;
    JoinGameScene* joinGameScene = nullptr;
    Shared<Net::ClientProtocol> protocol = nullptr;

    std::string host;
    std::string port;
    std::string username;

    QMediaPlayer* musicPlayer = nullptr;
    QAudioOutput* audioOutput = nullptr;

    void setUpWindow();

    void connectToServer();
    void clearCurrentScene();
    void showLobbyScene();
    void showWelcomeScene();
    void showGameCreationScene();
    void showJoinGameScene();
    void loadGames();
    void runGame();
};
#endif  // MAIN_WINDOW_H
