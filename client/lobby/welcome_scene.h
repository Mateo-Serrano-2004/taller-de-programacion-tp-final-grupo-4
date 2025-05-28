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
    void startClicked(QString username, QString ip, QString port);  // señal actualizada con ip y port

private:
    QLineEdit *nameInput;
    QLineEdit *ipInput;
    QLineEdit *portInput;
    QPushButton *startButton;
    void setUpWelcome();
};

#endif // WELCOME_SCENE_H
