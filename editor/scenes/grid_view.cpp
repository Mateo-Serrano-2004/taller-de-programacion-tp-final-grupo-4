#include "grid_view.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

void GridView::mousePressEvent(QMouseEvent* event) {
    QPointF pos = mapToScene(event->pos());
    int tileX = static_cast<int>(pos.x()) / 32;
    int tileY = static_cast<int>(pos.y()) / 32;
    if (tileX >= 0 && tileX < 50 && tileY >= 0 && tileY < 50) {
        emit cellClicked(tileX, tileY, event->button());
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
        int x = static_cast<int>(pos.x()) / 32;
        int y = static_cast<int>(pos.y()) / 32;
        if (x >= 0 && x < 50 && y >= 0 && y < 50) {
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
        int tileX = static_cast<int>(pos.x()) / 32;
        int tileY = static_cast<int>(pos.y()) / 32;
        if (tileX >= 0 && tileX < 50 && tileY >= 0 && tileY < 50) {
            emit cellClicked(tileX, tileY, Qt::LeftButton);
        }
    }
    QGraphicsView::mouseMoveEvent(event);
}