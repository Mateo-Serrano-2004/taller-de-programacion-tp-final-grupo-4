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
                    stop:0 #34495e, stop:1 #2c3e50);
                color: #ecf0f1;
                border: 2px solid #34495e;
                border-radius: 6px;
                padding: 8px 12px;
                font-size: 14px;
                font-weight: bold;
                selection-background-color: #3498db;
                selection-color: #ecf0f1;
            }
            QLineEdit:focus {
                border: 2px solid #3498db;
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #2c3e50, stop:1 #34495e);
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
