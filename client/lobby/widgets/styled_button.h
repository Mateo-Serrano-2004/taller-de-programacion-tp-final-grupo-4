#ifndef STYLED_BUTTON_H
#define STYLED_BUTTON_H

#include <QPushButton>

class StyledButton: public QPushButton {
    Q_OBJECT

public:
    explicit StyledButton(const QString& text, QWidget* parent = nullptr):
            QPushButton(text, parent) {
        setStyleSheet(R"(
            QPushButton {
                background-color: #4CAF50;
                color: white;
                border: none;
                border-radius: 4px;
                padding: 8px 16px;
                font-size: 14px;
                font-weight: bold;
            }
            QPushButton:hover {
                background-color: #45a049;
            }
            QPushButton:pressed {
                background-color: #3d8b40;
            }
        )");
    }
};

#endif  // STYLED_BUTTON_H
