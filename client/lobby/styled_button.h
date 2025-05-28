#ifndef STYLED_BUTTON_H
#define STYLED_BUTTON_H

#include <QPushButton>

class StyledButton : public QPushButton {
    public:
        StyledButton(const QString& text, QWidget* parent = nullptr)
        : QPushButton(text, parent) {
            setStyleSheet(R"(
                QPushButton {
                    background-color: rgba(255, 255, 255, 0.9);
                    color: #000000;
                    border: 1px solid #cccccc;
                    border-radius: 6px;
                    padding: 4px;
                }
                QPushButton:hover {
                    background-color: rgba(255, 255, 255, 1);
                }
            )");
        }
};

#endif // STYLED_BUTTON_H
