#ifndef GRID_ITEM_H
#define GRID_ITEM_H

#include <QGraphicsItem>
#include <QPen>

class GridItem: public QGraphicsItem {
public:
    GridItem(int width, int height, int tileSize, QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void setZoom(qreal zoom);

private:
    int gridWidth;
    int gridHeight;
    int tileSize;
    qreal zoomFactor = 1.0;
    QPen gridPen;
};

#endif  // GRID_ITEM_H
