#ifndef BACKGROUND_SCENE_H
#define BACKGROUND_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class BackgroundScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit BackgroundScene(QObject* parent = nullptr)
        : QGraphicsScene(parent) {
        QGraphicsPixmapItem* background = new QGraphicsPixmapItem(QPixmap("client/lobby/assets/welcome.jpg").scaled(640, 400));
        addItem(background);
    }
};

#endif // BACKGROUND_SCENE_H 