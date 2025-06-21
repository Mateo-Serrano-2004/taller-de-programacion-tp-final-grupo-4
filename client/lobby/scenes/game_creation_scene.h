#ifndef GAME_CREATIONSCENE_H
#define GAME_CREATIONSCENE_H

#include <QGraphicsScene>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>

#include "background_scene.h"

class GameCreationScene: public BackgroundScene {
    Q_OBJECT

public:
    explicit GameCreationScene(QObject* parent = nullptr);

    void setAvailableMaps(const QStringList& maps);

    void centerWidget(QGraphicsProxyWidget* proxy);

    ~GameCreationScene() override;

signals:
    void createGameRequested(const QString& gameName, const QString& selectedMap);
    void backClicked();

private:
    QListWidget* mapListWidget;
    QLineEdit* gameNameInput;
    QPushButton* createButton;
    void setUpGameCreation();
    bool isValidGameName(const QString& name);
    void updateCreateButtonState();
};

#endif  // GAMECREATIONSCENE_H
