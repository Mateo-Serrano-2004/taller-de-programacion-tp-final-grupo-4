#ifndef LOBBY_SCENE_H
#define LOBBY_SCENE_H

#include "background_scene.h"

class LobbyScene: public BackgroundScene {
    Q_OBJECT

public:
    explicit LobbyScene(QObject* parent = nullptr);
signals:
    void createClicked();
    void joinClicked();

private:
    void setUpLobby();
};

#endif
