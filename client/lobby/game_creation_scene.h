#ifndef GAME_CREATIONSCENE_H
#define GAME_CREATIONSCENE_H

#include <QGraphicsScene>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

class GameCreationScene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit GameCreationScene(QObject *parent = nullptr);

    void setAvailableMaps(const QStringList& maps);

    void centerWidget(QGraphicsProxyWidget* proxy);
signals:
    void createGameRequested(const QString& gameName, const QString& selectedMap);
    void backClicked();

private:
    QListWidget *mapListWidget;
    QLineEdit *gameNameInput;
    QPushButton *createButton;
    void setUpGameCreation();
};

#endif // GAMECREATIONSCENE_H

