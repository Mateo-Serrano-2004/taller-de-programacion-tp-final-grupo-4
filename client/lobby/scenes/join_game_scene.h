#ifndef JOIN_GAME_SCENE_H
#define JOIN_GAME_SCENE_H

#include <QGraphicsScene>
#include <QListWidget>
#include <QPushButton>
#include <QGraphicsProxyWidget>

#include "background_scene.h"

class JoinGameScene : public BackgroundScene {
    Q_OBJECT

public:
    explicit JoinGameScene(QObject *parent = nullptr);
    void setAvailableGames(const QStringList& games);

signals:
    void joinRequestedGame(const QString& gameName);
    void backClicked();
    void refreshClicked();

private:
    QListWidget* gameListWidget;
    QPushButton* joinButton;
    QGraphicsProxyWidget* mainWidgetProxy;
    void resizeScene(const QSizeF& size);
    void setUpJoin();
};

#endif // JOIN_GAME_SCENE_H
