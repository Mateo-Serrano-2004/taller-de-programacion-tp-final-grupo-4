#ifndef STYLED_LINE_EDIT_H
#define STYLED_LINE_EDIT_H

#include <QLineEdit>

class StyledLineEdit: public QLineEdit {
    Q_OBJECT
public:
    explicit StyledLineEdit(QWidget* parent = nullptr): QLineEdit(parent) {
        setStyleSheet(R"(
            QLineEdit {
                background-color: rgba(255, 255, 255, 0.9);
                color: #000000;
                border: 1px solid #cccccc;
                border-radius: 6px;
                padding: 4px;
            }
        )");
    }
};

#endif  // STYLED_LINE_EDIT_H
