#include "join_game_scene.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>

#include "styled_button.h"

JoinGameScene::JoinGameScene(QObject *parent)
    : QGraphicsScene(parent), mainWidgetProxy(nullptr)
{
    setUpJoin();
}

void JoinGameScene::setAvailableGames(const QStringList& games) {
    gameListWidget->clear();
    gameListWidget->addItems(games);
}

void JoinGameScene::resizeScene(const QSizeF& size) {
    if (mainWidgetProxy) {
        QPointF centerPos((size.width() - mainWidgetProxy->size().width()) / 2,
                          (size.height() - mainWidgetProxy->size().height()) / 2);
        mainWidgetProxy->setPos(centerPos);
    }
}

void JoinGameScene::setUpJoin() {
    QGraphicsPixmapItem* backround = new QGraphicsPixmapItem(QPixmap("client/lobby/assets/welcome.jpg").scaled(640, 400));
    addItem(backround);
    QLabel* title = new QLabel("Partidas disponibles:");
    title->setStyleSheet("color: white; font-size: 16px; font-weight: bold;");

    gameListWidget = new QListWidget();
    StyledButton* joinButton = new StyledButton("Unirse");
    StyledButton* refreshButton = new StyledButton("Refresh");
    refreshButton->setFixedWidth(80);

    QWidget* buttonRow = new QWidget();
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->setSpacing(10);
    buttonLayout->addWidget(joinButton);
    buttonLayout->addWidget(refreshButton);
    buttonRow->setLayout(buttonLayout);
    buttonRow->setStyleSheet("background: transparent;");

    QWidget* container = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(title);
    layout->addWidget(gameListWidget);
    layout->addWidget(buttonRow);
    container->setLayout(layout);
    container->setFixedWidth(350);
    container->setStyleSheet("background: transparent; color: white;");

    mainWidgetProxy = addWidget(container);
    resizeScene(sceneRect().size());

    connect(joinButton, &QPushButton::clicked, this, [this]() {
        QListWidgetItem* selected = gameListWidget->currentItem();
        if (selected) {
            emit joinRequestedGame(selected->text());
        }
    });
    connect(refreshButton, &QPushButton::clicked, this, &JoinGameScene::refreshClicked);

    QPushButton* backButton = new StyledButton("Volver");
    backButton->setFixedWidth(80);
    QWidget* backContainer = new QWidget();
    QHBoxLayout* backLayout = new QHBoxLayout();
    backLayout->setContentsMargins(0, 0, 0, 0);
    backLayout->setSpacing(0);
    backLayout->addWidget(backButton);
    backContainer->setLayout(backLayout);
    backContainer->setStyleSheet("background: transparent;");
    QGraphicsProxyWidget* backProxy = addWidget(backContainer);
    backProxy->setPos(10, 10);
    connect(backButton, &QPushButton::clicked, this, &JoinGameScene::backClicked);
}
