#ifndef JOIN_GAME_SCENE_H
#define JOIN_GAME_SCENE_H

#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QPushButton>
#include <QTableWidget>
#include <vector>

#include "common/DTO/game_info_dto.h"

#include "background_scene.h"

class JoinGameScene: public BackgroundScene {
    Q_OBJECT

public:
    explicit JoinGameScene(QObject* parent = nullptr);
    void setAvailableGames(const std::vector<DTO::GameInfoDTO>& games);
    int selectedGameId() const;

signals:
    void joinRequestedGame(const QString& gameName);
    void backClicked();
    void refreshClicked();

private:
    QTableWidget* gameTableWidget;
    QPushButton* joinButton;
    QGraphicsProxyWidget* mainWidgetProxy;
    void resizeScene(const QSizeF& size);
    void setUpJoin();
};

#endif  // JOIN_GAME_SCENE_H
