#include "main_window.h"

#include "client/game/dto_handler/event_dto_creator.h"
#include "client/game/event/username_event.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    setUpWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
    if (protocol) {
        delete protocol;
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
    connect(welcomeScene, &WelcomeScene::startClicked, this, [this](QString username, QString ip, QString port) {
        protocol = new Net::ClientProtocol(ip.toStdString(), port.toStdString());
        auto usernameEvent = std::make_shared<Model::UsernameEvent>(username.toStdString());
        DTO::EventDTOCreator creator(usernameEvent);
        protocol->send_event(creator);
        showLobbyScene();
    }, Qt::QueuedConnection);
}

void MainWindow::showLobbyScene() {
    clearCurrentScene();
    lobbyScene = new LobbyScene(this);
    ui->mainView->setScene(lobbyScene);
    connect(lobbyScene, &LobbyScene::createClicked, this, &MainWindow::showGameCreationScene, Qt::QueuedConnection);
    connect(lobbyScene, &LobbyScene::joinClicked, this, &MainWindow::showJoinGameScene, Qt::QueuedConnection);
}

void MainWindow::showGameCreationScene() {
    clearCurrentScene();
    gameCreationScene = new GameCreationScene(this);
    ui->mainView->setScene(gameCreationScene);
    connect(gameCreationScene, &GameCreationScene::backClicked, this, &MainWindow::showLobbyScene, Qt::QueuedConnection);
}

void MainWindow::showJoinGameScene() {
    clearCurrentScene();
    joinGameScene = new JoinGameScene(this);
    ui->mainView->setScene(joinGameScene);
    connect(joinGameScene, &JoinGameScene::backClicked, this, &MainWindow::showLobbyScene, Qt::QueuedConnection);
}

void MainWindow::onPushButtonClicked() {
    showLobbyScene();
}

void MainWindow::receiveAvailableGames(const QStringList& partidas) {
    if (!joinGameScene) {
        showJoinGameScene();
    }
    joinGameScene->setAvailableGames(partidas);
    ui->mainView->setScene(joinGameScene);
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

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    if (ui->mainView->scene()) {
        ui->mainView->fitInView(ui->mainView->scene()->sceneRect(), Qt::KeepAspectRatio);
    }
}

void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
    if (ui->mainView->scene()) {
        ui->mainView->fitInView(ui->mainView->scene()->sceneRect(), Qt::KeepAspectRatio);
    }
}
