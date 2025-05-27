#include "main_window.h"
#include "./ui_main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    setUpWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPushButtonClicked() {
    ui->mainView->setScene(lobbyScene);
}

void MainWindow::receiveAvailableGames(const QStringList& partidas) {
    joinGameScene->setAvailableGames(partidas);
    ui->mainView->setScene(joinGameScene);
}

void MainWindow::setUpWindow() {
    ui->setupUi(this);
    this->setFixedSize(640, 400);

    this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);
    this->setWindowFlag(Qt::WindowMinimizeButtonHint, true);

    ui->mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    welcomeScene->setSceneRect(0, 0, 640, 400);
    session = new GameSession(this);
    lobbyScene = new LobbyScene(this);
    gameCreationScene = new GameCreationScene(this);
    joinGameScene = new JoinGameScene(this);

    connect(welcomeScene, &WelcomeScene::startClicked, this, [this](QString username) {
        session->setUsername(username);
        ui->mainView->setScene(lobbyScene);
    });

    
    connect(lobbyScene, &LobbyScene::createClicked, this, [this]() {
        ui->mainView->setScene(gameCreationScene);
    });

    connect(lobbyScene, &LobbyScene::createClicked, this, [this]() {
        QStringList mapsTester = { "Desierto", "Pueblito Azteca", "Zona de entrenamiento" };
        gameCreationScene->setAvailableMaps(mapsTester);

        ui->mainView->setScene(gameCreationScene);
    });

    
    connect(lobbyScene, &LobbyScene::joinClicked, this, [this]() {
        ui->mainView->setScene(joinGameScene);
    });

    connect(gameCreationScene, &GameCreationScene::createdGame, this, [this](const QString& gameName, const QString& selectedMap) {
        session->setGameName(gameName);
        session->setMap(selectedMap);
        //PENDING: CONECTAR CON SDL: startSDLGame();
    });

}

void MainWindow::startSDLGame() {
    this->close();

    launchGame(user, map);
}