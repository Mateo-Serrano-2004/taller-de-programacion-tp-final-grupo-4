#ifndef WELCOME_SCENE_H
#define WELCOME_SCENE_H

#include <QGraphicsScene>
#include <QLineEdit>
#include <QPushButton>

class WelcomeScene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit WelcomeScene(QObject *parent = nullptr);

signals:
    void startClicked(QString username);  // pressed button "Ingresar" signal

private:
    QLineEdit *nameInput;
    QPushButton *startButton;
    void setUpWelcome();
};

#endif // WELCOME_SCENE_H
