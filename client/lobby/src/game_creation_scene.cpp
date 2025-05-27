#include "game_creation_scene.h"
#include <QGraphicsProxyWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include "styled_button.h"

GameCreationScene::GameCreationScene(QObject *parent)
    : QGraphicsScene(parent),
    mapListWidget(new QListWidget),
    gameNameInput(new QLineEdit)
{
    setUpGameCreation();
}

void GameCreationScene::setAvailableMaps(const QStringList& maps) {
    mapListWidget->clear();
    mapListWidget->addItems(maps);
}

void GameCreationScene::centerWidget(QGraphicsProxyWidget* proxy) {
    QRectF sceneBounds = sceneRect();
    QSizeF widgetSize = proxy->size();
    QPointF centerPos((sceneBounds.width() - widgetSize.width()) / 2,
                      (sceneBounds.height() - widgetSize.height()) / 2);
    proxy->setPos(centerPos);
}

void GameCreationScene::setUpGameCreation() {
    QGraphicsPixmapItem* backround = new QGraphicsPixmapItem(QPixmap(":/assets/welcome1.jpg").scaled(640, 400));
    addItem(backround);
    QLabel *mapLabel = new QLabel("Seleccioná un mapa:");
    mapLabel->setStyleSheet("color: white; font-weight: bold; font-size: 14px;");

    QLabel *nameLabel = new QLabel("Partida:");
    nameLabel->setStyleSheet("color: white; font-weight: bold; font-size: 14px;");

    gameNameInput->setPlaceholderText("Inserte el nombre");
    StyledButton* createButton = new StyledButton("Crear");


    QWidget *container = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(mapLabel);
    mainLayout->addWidget(mapListWidget);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(gameNameInput);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(createButton);
    container->setLayout(mainLayout);
    container->setStyleSheet("background: transparent; color: white;");
    container->setFixedWidth(400);

    QGraphicsProxyWidget *proxy = addWidget(container);
    centerWidget(proxy);

    connect(createButton, &QPushButton::clicked, this, [this]() {
        QString gameName = gameNameInput->text();
        QListWidgetItem *selectedItem = mapListWidget->currentItem();
        if (!gameName.isEmpty() && selectedItem) {
            emit createdGame(gameName, selectedItem->text());
        }
    });
}
