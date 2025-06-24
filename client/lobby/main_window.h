#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QSoundEffect>
#include <QTimer>
#include <string>

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
    void playBackgroundMusic();

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

    QTimer* musicTimer = nullptr;
    QSoundEffect* backgroundMusic = nullptr;
    bool musicPlaying = false;

    void setUpWindow();

    void connectToServer();
    void clearCurrentScene();
    void showLobbyScene();
    void showWelcomeScene();
    void showGameCreationScene();
    void showJoinGameScene();
    void loadGames();
    void runGame();
    void restartBackgroundMusic();
    void setupMusic();
    void setupGraphicsView();
    void setupWindowProperties();
    void handleGameCreationRequest(const QString& gameName, const QString& selectedMap);
    void handleJoinGameRequest();
    void handleWelcomeStart(const QString& username, const QString& ip, const QString& port);
    void handleServerConnectionError();
};
#endif  // MAIN_WINDOW_H
