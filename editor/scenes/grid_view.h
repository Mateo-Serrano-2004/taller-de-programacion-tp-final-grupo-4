#ifndef GRID_VIEW_H
#define GRID_VIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QWheelEvent>

class GridView: public QGraphicsView {
    Q_OBJECT
public:
    explicit GridView(QGraphicsScene* scene, QWidget* parent = nullptr):
            QGraphicsView(scene, parent) {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        setStyleSheet("background: white;");
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    }

signals:
    void cellClicked(int x, int y, Qt::MouseButton button);
    void cellDropped(int x, int y, int assetIndex);
    void cellTileSelected(int x, int y);

protected:
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
};

#endif  // GRID_VIEW_H
