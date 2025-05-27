#ifndef STYLED_BUTTON_H
#define STYLED_BUTTON_H
#include <QPushButton>

class StyledButton : public QPushButton {
    public:
        StyledButton(const QString& text, QWidget* parent = nullptr)
        : QPushButton(text, parent) {
                              setStyleSheet(R"(
        QPushButton {
            background-color: rgba(255, 255, 255, 0.8);
            color: #000000;
            border: 2px solid #ffffff;
            border-radius: 8px;
            padding: 6px 12px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: rgba(255, 255, 255, 1);
        }
        )");
}
};

#endif // STYLED_BUTTON_H
