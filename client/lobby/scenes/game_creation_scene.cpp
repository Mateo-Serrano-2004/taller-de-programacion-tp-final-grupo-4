#include "game_creation_scene.h"

#include <QGraphicsProxyWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QDebug>
#include <QDir>
#include <QFile>

#include "../widgets/styled_button.h"

GameCreationScene::GameCreationScene(QObject *parent)
    : BackgroundScene(parent),
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
    QLabel *mapLabel = new QLabel("Seleccioná un mapa:");
    mapLabel->setStyleSheet("color: white; font-weight: bold; font-size: 14px;");

    QLabel *nameLabel = new QLabel("Partida:");
    nameLabel->setStyleSheet("color: white; font-weight: bold; font-size: 14px;");

    gameNameInput->setPlaceholderText("Inserte el nombre");
    StyledButton* createButton = new StyledButton("Crear");

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
    connect(backButton, &QPushButton::clicked, this, &GameCreationScene::backClicked);

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
            emit createGameRequested(gameName, selectedItem->text());
        }
    });
}
