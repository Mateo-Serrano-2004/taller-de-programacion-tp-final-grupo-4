#ifndef WELCOME_SCENE_H
#define WELCOME_SCENE_H

#include <QGraphicsScene>
#include <QLineEdit>

#include "background_scene.h"

class WelcomeScene: public BackgroundScene {
    Q_OBJECT

public:
    explicit WelcomeScene(QObject* parent = nullptr);

signals:
    void startClicked(const QString& username, const QString& ip, const QString& port);

private:
    void setUpWelcome();
    QLineEdit* nameInput;
    QLineEdit* ipInput;
    QLineEdit* portInput;
};

#endif  // WELCOME_SCENE_H
