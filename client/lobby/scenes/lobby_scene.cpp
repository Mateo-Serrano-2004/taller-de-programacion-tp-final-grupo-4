#include "lobby_scene.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QWidget>

#include "../widgets/styled_button.h"


LobbyScene::LobbyScene(QObject* parent): BackgroundScene(parent) { setUpLobby(); }

void LobbyScene::setUpLobby() {
    StyledButton* createButton = new StyledButton("Crear Partida");
    StyledButton* joinButton = new StyledButton("Unirse a partida");

    QWidget* container = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(createButton);
    layout->addWidget(joinButton);
    container->setLayout(layout);
    container->setFixedWidth(200);
    container->setFixedHeight(150);
    container->setStyleSheet("background: transparent; color: white;");

    QGraphicsProxyWidget* proxy = addWidget(container);
    proxy->setPos(15, 150);

    connect(createButton, &QPushButton::clicked, this, &LobbyScene::createClicked);
    connect(joinButton, &QPushButton::clicked, this, &LobbyScene::joinClicked);
}
