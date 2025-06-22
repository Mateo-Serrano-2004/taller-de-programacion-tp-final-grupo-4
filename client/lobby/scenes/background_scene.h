#ifndef BACKGROUND_SCENE_H
#define BACKGROUND_SCENE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class BackgroundScene: public QGraphicsScene {
    Q_OBJECT
public:
    explicit BackgroundScene(QObject* parent = nullptr): QGraphicsScene(parent) {
        QGraphicsPixmapItem* background =
                new QGraphicsPixmapItem(QPixmap(":/assets/gfx/welcome.jpg").scaled(640, 400));
        addItem(background);
    }
};

#endif  // BACKGROUND_SCENE_H
