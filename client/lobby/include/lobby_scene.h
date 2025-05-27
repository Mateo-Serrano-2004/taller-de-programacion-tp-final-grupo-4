#ifndef LOBBY_SCENE_H
#define LOBBY_SCENE_H

#include <QGraphicsScene>
#include <QPushButton>

class LobbyScene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit LobbyScene(QObject *parent = nullptr);
signals:
    void createClicked();
    void joinClicked();

private:
    void setUpLobby();
};

#endif
