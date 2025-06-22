#ifndef ERROR_DIALOG_H
#define ERROR_DIALOG_H

#include <QGraphicsView>
#include <QMessageBox>

class ErrorDialog {
public:
    static void showError(const QString& message, QGraphicsScene* scene = nullptr) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText(message);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStyleSheet(R"(
            QMessageBox {
                background-color: white;
                border: 1px solid #cccccc;
                border-radius: 6px;
            }
            QMessageBox QLabel {
                color: black;
                font-size: 12px;
            }
            QPushButton {
                background-color: #f0f0f0;
                border: 1px solid #cccccc;
                border-radius: 4px;
                padding: 5px 15px;
            }
            QPushButton:hover {
                background-color: #e0e0e0;
            }
        )");

        if (scene && !scene->views().isEmpty()) {
            QGraphicsView* view = scene->views().first();
            QPoint center = view->mapToGlobal(view->viewport()->rect().center());
            msgBox.move(center.x() - msgBox.width() / 2, center.y() - msgBox.height() / 2);
        }

        msgBox.exec();
    }
};

#endif  // ERROR_DIALOG_H
