#include "lobby_scene.h"
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include "styled_button.h"


LobbyScene::LobbyScene(QObject *parent) : QGraphicsScene(parent) {
    setUpLobby();
}

void LobbyScene::setUpLobby() {
    QGraphicsPixmapItem* fondoItem = new QGraphicsPixmapItem(QPixmap(":/assets/welcome1.jpg").scaled(640, 400));
    addItem(fondoItem);
    StyledButton* createButton = new StyledButton("Crear Partida");
    addWidget(createButton)->setPos(255, 130);
    connect(createButton, &QPushButton::clicked, this, &LobbyScene::createClicked);

    StyledButton* joinButton = new StyledButton("Unirse a partida");
    addWidget(joinButton)->setPos(250, 180);
    connect(joinButton, &QPushButton::clicked, this, &LobbyScene::joinClicked);
}
