#ifndef STYLED_LINE_EDIT_H
#define STYLED_LINE_EDIT_H

#include <QLineEdit>

class StyledLineEdit: public QLineEdit {
    Q_OBJECT
public:
    explicit StyledLineEdit(QWidget* parent = nullptr): QLineEdit(parent) {
        setStyleSheet(R"(
            QLineEdit {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 rgba(52, 73, 94, 0.8), stop:1 rgba(44, 62, 80, 0.8));
                color: #ecf0f1;
                border: 2px solid rgba(255, 255, 255, 0.3);
                border-radius: 6px;
                padding: 6px 10px;
                font-size: 12px;
                font-weight: bold;
                selection-background-color: #3498db;
                selection-color: #ecf0f1;
            }
            QLineEdit:focus {
                border: 2px solid #3498db;
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 rgba(52, 73, 94, 0.9), stop:1 rgba(44, 62, 80, 0.9));
            }
            QLineEdit:hover {
                border: 2px solid #5dade2;
            }
            QLineEdit::placeholder {
                color: #bdc3c7;
                font-style: italic;
            }
        )");
    }
};

#endif  // STYLED_LINE_EDIT_H
