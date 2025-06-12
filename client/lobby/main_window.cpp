#include "main_window.h"

#include <list>
#include <memory>
#include <string>
#include <iostream>

#include "client/game/cs2d_app.h"
#include "client/game/dto_handler/event_dto_creator.h"
#include "client/game/event/create_game_event.h"
#include "client/game/event/join_game_event.h"
#include "client/game/event/request_games_list_event.h"
#include "client/game/event/request_maps_event.h"
#include "client/game/event/username_event.h"
#include "common/DTO/game_info_dto.h"
#include "common/definitions.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    musicPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(QAudioFormat(), this);
    audioOutput->setVolume(0.1f);
    musicPlayer->setMedia(QUrl("qrc:/assets/Menu_Theme.mp3"));
    musicPlayer->setPlaylist(new QMediaPlaylist());
    musicPlayer->playlist()->addMedia(QUrl("qrc:/assets/Menu_Theme.mp3"));
    musicPlayer->playlist()->setPlaybackMode(QMediaPlaylist::Loop);
    musicPlayer->play();
    setUpWindow();
}

MainWindow::~MainWindow() {
    delete ui;
    if (protocol) {
        delete protocol;
    }
    delete musicPlayer;
    delete audioOutput;
}

void MainWindow::runGame() {
    this->hide();
    try {
        App::CS2DApp game(protocol);
        game.launch();
    } catch (...) {
        QApplication::quit();
        return;
    }
    this->show();
    showLobbyScene();
}

void MainWindow::loadGames() {
    auto requestGamesListEvent = make_shared<Model::RequestGamesListEvent>();
    DTO::EventDTOCreator creator(requestGamesListEvent);
    protocol->send_event(creator);

    std::list<GameInfoDTO> games = protocol->receive_game_list();
    joinGameScene->setAvailableGames(games);
}

void MainWindow::clearCurrentScene() {
    QGraphicsScene* current = qobject_cast<QGraphicsScene*>(ui->mainView->scene());
    if (current) {
        ui->mainView->setScene(nullptr);
        current->disconnect();
        delete current;
    }
    welcomeScene = nullptr;
    lobbyScene = nullptr;
    gameCreationScene = nullptr;
    joinGameScene = nullptr;
}

void MainWindow::showWelcomeScene() {
    clearCurrentScene();
    welcomeScene = new WelcomeScene(this);
    ui->mainView->setScene(welcomeScene);
    connect(
            welcomeScene, &WelcomeScene::startClicked, this,
            [this](QString username, QString ip, QString port) {
                protocol = new Net::ClientProtocol(ip.toStdString(), port.toStdString());
                auto usernameEvent = make_shared<Model::UsernameEvent>(username.toStdString());
                DTO::EventDTOCreator creator(usernameEvent);
                protocol->send_event(creator);

                showLobbyScene();
            },
            Qt::QueuedConnection);
}

void MainWindow::showLobbyScene() {
    clearCurrentScene();
    lobbyScene = new LobbyScene(this);
    ui->mainView->setScene(lobbyScene);
    connect(lobbyScene, &LobbyScene::createClicked, this, &MainWindow::showGameCreationScene,
            Qt::QueuedConnection);
    connect(lobbyScene, &LobbyScene::joinClicked, this, &MainWindow::showJoinGameScene,
            Qt::QueuedConnection);
}

void MainWindow::showGameCreationScene() {
    clearCurrentScene();
    gameCreationScene = new GameCreationScene(this);
    ui->mainView->setScene(gameCreationScene);
    connect(gameCreationScene, &GameCreationScene::backClicked, this, &MainWindow::showLobbyScene,
            Qt::QueuedConnection);
    connect(
            gameCreationScene, &GameCreationScene::createGameRequested, this,
            [this](const QString& gameName, const QString& selectedMap) {
                auto createGameEvent = std::make_shared<Model::CreateGameEvent>(
                        gameName.toStdString(), selectedMap.toStdString());
                DTO::EventDTOCreator creator(createGameEvent);
                protocol->send_event(creator);
                runGame();
            },
            Qt::QueuedConnection);

    auto requestMapsEvent = std::make_shared<Model::RequestMapsEvent>();
    DTO::EventDTOCreator creator(requestMapsEvent);
    protocol->send_event(creator);

    std::list<std::string> maps = protocol->receive_map_list();
    QStringList qMaps;
    for (const auto& map: maps) {
        qMaps << QString::fromStdString(map);
    }
    gameCreationScene->setAvailableMaps(qMaps);
}

void MainWindow::showJoinGameScene() {
    clearCurrentScene();
    joinGameScene = new JoinGameScene(this);
    ui->mainView->setScene(joinGameScene);
    connect(joinGameScene, &JoinGameScene::backClicked, this, &MainWindow::showLobbyScene,
            Qt::QueuedConnection);
    connect(
            joinGameScene, &JoinGameScene::joinRequestedGame, this,
            [this](const QString&) {
                int partida_id = joinGameScene->selectedGameId();
                if (partida_id != -1) {
                    auto joinGameEvent = make_shared<Model::JoinGameEvent>(partida_id);
                    DTO::EventDTOCreator creator(joinGameEvent);
                    protocol->send_event(creator);
                    runGame();
                }
            },
            Qt::QueuedConnection);
    connect(
            joinGameScene, &JoinGameScene::refreshClicked, this, [this]() { loadGames(); },
            Qt::QueuedConnection);

    loadGames();
}

void MainWindow::onPushButtonClicked() { showLobbyScene(); }

void MainWindow::receiveAvailableMaps(const QStringList& maps) {
    if (gameCreationScene) {
        gameCreationScene->setAvailableMaps(maps);
    }
}

void MainWindow::setUpWindow() {
    ui->setupUi(this);
    this->setMinimumSize(640, 400);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->mainView->setBackgroundBrush(QBrush(Qt::black));
    ui->mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->mainView->setRenderHint(QPainter::SmoothPixmapTransform);
    ui->mainView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    showWelcomeScene();

    if (ui->mainView->scene()) {
        ui->mainView->fitInView(ui->mainView->scene()->sceneRect(), Qt::KeepAspectRatio);
    }
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    if (ui->mainView->scene()) {
        ui->mainView->fitInView(ui->mainView->scene()->sceneRect(), Qt::KeepAspectRatio);
    }
}

void MainWindow::showEvent(QShowEvent* event) {
    QMainWindow::showEvent(event);
    if (ui->mainView->scene()) {
        ui->mainView->fitInView(ui->mainView->scene()->sceneRect(), Qt::KeepAspectRatio);
    }
}
