#ifndef STYLED_BUTTON_H
#define STYLED_BUTTON_H

#include <QPushButton>
#include <QSound>

class StyledButton: public QPushButton {
    Q_OBJECT

public:
    explicit StyledButton(const QString& text, QWidget* parent = nullptr):
            QPushButton(text, parent) {
        setStyleSheet(R"(
            QPushButton {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #2c3e50, stop:1 #34495e);
                color: #ecf0f1;
                border: 2px solid #34495e;
                border-radius: 8px;
                padding: 10px 20px;
                font-size: 13px;
                font-weight: bold;
                min-height: 25px;
                min-width: 80px;
            }
            QPushButton:hover {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #34495e, stop:1 #2c3e50);
                border: 2px solid #3498db;
                color: #3498db;
            }
            QPushButton:pressed {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #1a252f, stop:1 #2c3e50);
                border: 2px solid #2980b9;
                color: #2980b9;
            }
            QPushButton:disabled {
                background: #7f8c8d;
                border: 2px solid #95a5a6;
                color: #bdc3c7;
            }
        )");

        setupSound();
    }

private:
    void setupSound() {
        connect(this, &QPushButton::clicked, this,
                []() { QSound::play("qrc:/assets/sfx/wpn_select.wav"); });
    }
};

#endif  // STYLED_BUTTON_H
