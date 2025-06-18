#include "grid_item.h"

#include <QPainter>

GridItem::GridItem(int width, int height, int tileSize, QGraphicsItem* parent):
        QGraphicsItem(parent),
        gridWidth(width),
        gridHeight(height),
        tileSize(tileSize),
        gridPen(Qt::gray) {
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemIsMovable, false);
}

QRectF GridItem::boundingRect() const {
    return QRectF(0, 0, gridWidth * tileSize * zoomFactor, gridHeight * tileSize * zoomFactor);
}

void GridItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->save();
    painter->scale(zoomFactor, zoomFactor);

    painter->fillRect(QRectF(0, 0, gridWidth * tileSize, gridHeight * tileSize), Qt::white);
    for (int y = 0; y <= gridHeight; ++y) {
        painter->drawLine(0, y * tileSize, gridWidth * tileSize, y * tileSize);
    }
    for (int x = 0; x <= gridWidth; ++x) {
        painter->drawLine(x * tileSize, 0, x * tileSize, gridHeight * tileSize);
    }
    painter->restore();
}

void GridItem::setZoom(qreal zoom) {
    prepareGeometryChange();
    zoomFactor = zoom;
}
