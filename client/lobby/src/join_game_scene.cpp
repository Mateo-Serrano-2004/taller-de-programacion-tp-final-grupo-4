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
    QGraphicsPixmapItem* backround = new QGraphicsPixmapItem(QPixmap(":/assets/welcome1.jpg").scaled(640, 400));
    addItem(backround);
    QLabel* title = new QLabel("Partidas disponibles:");
    title->setStyleSheet("color: white; font-size: 16px; font-weight: bold;");

    gameListWidget = new QListWidget();
    StyledButton* joinButton = new StyledButton("Unirse");

    QWidget* container = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(title);
    layout->addWidget(gameListWidget);
    layout->addWidget(joinButton);
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
}
