#include "main_window.h"

#include <QMessageBox>
#include <memory>

#include "client/exception/closed_app.h"
#include "client/exception/closed_game.h"
#include "client/game/cs2d_app.h"
#include "client/game/event/create_game_event.h"
#include "client/game/event/join_game_event.h"
#include "client/game/event/request_games_list_event.h"
#include "client/game/event/request_maps_event.h"
#include "client/game/event/username_event.h"
#include "common/DTO/game_info_dto.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    setUpWindow();
}

MainWindow::~MainWindow() {
    delete ui;
    delete backgroundMusic;
}

void MainWindow::connectToServer() {
    try {
        protocol.reset();
        protocol = make_shared<Net::ClientProtocol>(host, port);
        auto usernameEvent = make_shared<Model::UsernameEvent>(username);
        protocol->send_event(usernameEvent->as_dto());
    } catch (const std::exception&) {
        handleServerConnectionError();
    }
}

void MainWindow::handleServerConnectionError() {
    QMessageBox::critical(
            this, "Error de Conexión",
            "No se pudo conectar al servidor. El servidor puede estar cerrado o no disponible.");
    clearCurrentScene();
    QApplication::quit();
}

void MainWindow::runGame() {
    this->hide();

    musicTimer->stop();
    musicPlaying = false;
    backgroundMusic->stop();

    try {
        App::CS2DApp game(protocol);
        game.launch();
    } catch (const ClosedAppException&) {
        clearCurrentScene();
        QApplication::quit();
        return;
    }

    connectToServer();
    this->show();
    this->resize(640, 400);
    restartBackgroundMusic();
    showLobbyScene();
}

void MainWindow::loadGames() {
    try {
        auto requestGamesListEvent = make_shared<Model::RequestGamesListEvent>();
        protocol->send_event(requestGamesListEvent->as_dto());

        auto games = std::get<DTO::GameListDTO>(protocol->receive_variant());
        joinGameScene->setAvailableGames(games.games);
    } catch (const std::exception&) {
        handleServerConnectionError();
    }
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
                handleWelcomeStart(username, ip, port);
            },
            Qt::QueuedConnection);
}

void MainWindow::handleWelcomeStart(const QString& username, const QString& ip,
                                    const QString& port) {
    this->host = ip.toStdString();
    this->port = port.toStdString();
    this->username = username.toStdString();
    connectToServer();
    showLobbyScene();
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
                handleGameCreationRequest(gameName, selectedMap);
            },
            Qt::QueuedConnection);

    try {
        auto requestMapsEvent = std::make_shared<Model::RequestMapsEvent>();
        protocol->send_event(requestMapsEvent->as_dto());

        auto map_name_list = std::get<DTO::MapNameListDTO>(protocol->receive_variant());
        QStringList qMaps;
        for (const auto& map: map_name_list.maps_names) qMaps << QString::fromStdString(map);

        gameCreationScene->setAvailableMaps(qMaps);
    } catch (const std::exception&) {
        handleServerConnectionError();
    }
}

void MainWindow::handleGameCreationRequest(const QString& gameName, const QString& selectedMap) {
    try {
        auto createGameEvent = std::make_shared<Model::CreateGameEvent>(gameName.toStdString(),
                                                                        selectedMap.toStdString());
        protocol->send_event(createGameEvent->as_dto());
        runGame();
    } catch (const std::exception&) {
        handleServerConnectionError();
    }
}

void MainWindow::showJoinGameScene() {
    clearCurrentScene();
    joinGameScene = new JoinGameScene(this);
    ui->mainView->setScene(joinGameScene);
    connect(joinGameScene, &JoinGameScene::backClicked, this, &MainWindow::showLobbyScene,
            Qt::QueuedConnection);
    connect(
            joinGameScene, &JoinGameScene::joinRequestedGame, this,
            [this](const QString&) { handleJoinGameRequest(); }, Qt::QueuedConnection);
    connect(
            joinGameScene, &JoinGameScene::refreshClicked, this, [this]() { loadGames(); },
            Qt::QueuedConnection);

    loadGames();
}

void MainWindow::handleJoinGameRequest() {
    int partida_id = joinGameScene->selectedGameId();
    if (partida_id != -1) {
        try {
            auto joinGameEvent = make_shared<Model::JoinGameEvent>(partida_id);
            protocol->send_event(joinGameEvent->as_dto());
            runGame();
        } catch (const std::exception&) {
            handleServerConnectionError();
        }
    }
}

void MainWindow::onPushButtonClicked() { showLobbyScene(); }

void MainWindow::receiveAvailableMaps(const QStringList& maps) {
    if (gameCreationScene) {
        gameCreationScene->setAvailableMaps(maps);
    }
}

void MainWindow::playBackgroundMusic() {
    if (backgroundMusic) {
        backgroundMusic->play();
    }
}

void MainWindow::setUpWindow() {
    ui->setupUi(this);
    setupWindowProperties();
    setupGraphicsView();
    setupMusic();
    showWelcomeScene();

    if (ui->mainView->scene()) {
        ui->mainView->fitInView(ui->mainView->scene()->sceneRect(), Qt::KeepAspectRatio);
    }
}

void MainWindow::setupWindowProperties() {
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

void MainWindow::setupGraphicsView() {
    ui->mainView->setBackgroundBrush(QBrush(Qt::black));
    ui->mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->mainView->setRenderHint(QPainter::SmoothPixmapTransform);
    ui->mainView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

void MainWindow::setupMusic() {
    backgroundMusic = new QSoundEffect(this);
    backgroundMusic->setSource(QUrl("qrc:/assets/sfx/menu.wav"));
    backgroundMusic->setVolume(0.3);

    connect(backgroundMusic, &QSoundEffect::statusChanged, this, [this]() {
        if (backgroundMusic->status() == QSoundEffect::Ready) {
            backgroundMusic->setLoopCount(QSoundEffect::Infinite);
            backgroundMusic->play();
        }
    });

    musicTimer = new QTimer(this);
    connect(musicTimer, &QTimer::timeout, this, &MainWindow::playBackgroundMusic);
    musicTimer->setInterval(43000);
    musicTimer->start();
    musicPlaying = true;
}

void MainWindow::restartBackgroundMusic() {
    musicTimer->start();
    musicPlaying = true;
    backgroundMusic->play();
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
