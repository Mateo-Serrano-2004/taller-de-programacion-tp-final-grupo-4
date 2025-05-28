#include "main_window.h"
#include "ui_main_window.h"

#include "common/definitions.h"
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

void MainWindow::onPushButtonClicked() {
    ui->mainView->setScene(lobbyScene);
}

void MainWindow::receiveAvailableGames(const QStringList& partidas) {
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

    welcomeScene = new WelcomeScene(this);
    welcomeScene->setSceneRect(0, 0, 640, 400);

    lobbyScene = new LobbyScene(this);
    ui->mainView->setScene(welcomeScene);

    connect(welcomeScene, &WelcomeScene::startClicked, this, [this](QString username, QString ip, QString port) {
        protocol = new Net::ClientProtocol(ip.toStdString(), port.toStdString());

        auto usernameEvent = make_shared<Model::UsernameEvent>(username.toStdString()); 
        DTO::EventDTOCreator creator(usernameEvent);

        protocol->send_event(creator);
        ui->mainView->setScene(lobbyScene);
    });

    gameCreationScene = new GameCreationScene(this);

    connect(lobbyScene, &LobbyScene::createClicked, this, [this]() {
        ui->mainView->setScene(gameCreationScene);
    });

    connect(lobbyScene, &LobbyScene::createClicked, this, [this]() {
        QStringList mapsTester = { "Desierto", "Pueblito Azteca", "Zona de entrenamiento" };
        gameCreationScene->setAvailableMaps(mapsTester);
        ui->mainView->setScene(gameCreationScene);
    });
    
    joinGameScene = new JoinGameScene(this);
    
    connect(lobbyScene, &LobbyScene::joinClicked, this, [this]() {
        ui->mainView->setScene(joinGameScene);
    });

    connect(gameCreationScene, &GameCreationScene::backClicked, this, [this]() {
        ui->mainView->setScene(lobbyScene);
    });
    connect(joinGameScene, &JoinGameScene::backClicked, this, [this]() {
        ui->mainView->setScene(lobbyScene);
    });

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
