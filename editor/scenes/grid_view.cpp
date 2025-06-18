#include "grid_view.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

#include "constants.h"

void GridView::mousePressEvent(QMouseEvent* event) {
    QPointF pos = mapToScene(event->pos());
    int tileX = static_cast<int>(pos.x()) / TILE_SIZE;
    int tileY = static_cast<int>(pos.y()) / TILE_SIZE;
    if (tileX >= 0 && tileX < MAP_WIDTH && tileY >= 0 && tileY < MAP_HEIGHT) {
        if (event->button() == Qt::MiddleButton) {
            emit cellTileSelected(tileX, tileY);
        } else {
            emit cellClicked(tileX, tileY, event->button());
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void GridView::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasFormat("application/x-asset-index")) {
        event->acceptProposedAction();
    }
}

void GridView::dropEvent(QDropEvent* event) {
    if (event->mimeData()->hasFormat("application/x-asset-index")) {
        QPointF pos = mapToScene(event->pos());
        int x = static_cast<int>(pos.x()) / TILE_SIZE;
        int y = static_cast<int>(pos.y()) / TILE_SIZE;
        if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
            QByteArray itemData = event->mimeData()->data("application/x-asset-index");
            int assetIndex = itemData.toInt();
            emit cellDropped(x, y, assetIndex);
            event->acceptProposedAction();
        }
    }
}

void GridView::wheelEvent(QWheelEvent* event) {
    if (event->modifiers() & Qt::ControlModifier) {
        double scaleFactor = 1.15;
        if (event->angleDelta().y() > 0)
            scale(scaleFactor, scaleFactor);
        else
            scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    } else {
        QGraphicsView::wheelEvent(event);
    }
}

void GridView::dragMoveEvent(QDragMoveEvent* event) {
    if (event->mimeData()->hasFormat("application/x-asset-index")) {
        event->acceptProposedAction();
    }
}

void GridView::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        QPointF pos = mapToScene(event->pos());
        int tileX = static_cast<int>(pos.x()) / TILE_SIZE;
        int tileY = static_cast<int>(pos.y()) / TILE_SIZE;
        if (tileX >= 0 && tileX < MAP_WIDTH && tileY >= 0 && tileY < MAP_HEIGHT) {
            emit cellClicked(tileX, tileY, Qt::LeftButton);
        }
    } else if (event->buttons() & Qt::RightButton) {
        QPointF pos = mapToScene(event->pos());
        int tileX = static_cast<int>(pos.x()) / TILE_SIZE;
        int tileY = static_cast<int>(pos.y()) / TILE_SIZE;
        if (tileX >= 0 && tileX < MAP_WIDTH && tileY >= 0 && tileY < MAP_HEIGHT) {
            emit cellClicked(tileX, tileY, Qt::RightButton);
        }
    }
    QGraphicsView::mouseMoveEvent(event);
}
