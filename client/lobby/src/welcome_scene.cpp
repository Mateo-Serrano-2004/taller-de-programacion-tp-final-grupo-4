#include "welcome_scene.h"

#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QHBoxLayout>
#include <QLabel>

#include "styled_button.h"

WelcomeScene::WelcomeScene(QObject *parent) : QGraphicsScene(parent) {
    setUpWelcome();
}

void WelcomeScene::setUpWelcome() {
    QGraphicsPixmapItem* backround = new QGraphicsPixmapItem(QPixmap(":/assets/welcome1.jpg").scaled(640, 400));
    addItem(backround);
    QPixmap logo(":/assets/Counter-Strike-Logo.png");
    logo = logo.scaledToHeight(100, Qt::SmoothTransformation);
    QGraphicsPixmapItem* logoItem = addPixmap(logo);
    logoItem->setPos(120, 70);

    QLabel *textLabel = new QLabel("¡Bienvenido!");
    textLabel->setStyleSheet("QLabel { color: white; font-size: 16px; font-weight: bold; }");

    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Inserte su username");
    nameInput->setFixedWidth(180);
    nameInput->setStyleSheet(R"(
        QLineEdit {
            background-color: rgba(255, 255, 255, 0.9);
            color: #000000;
            border: 1px solid #cccccc;
            border-radius: 6px;
            padding: 4px;
        }
    )");

    StyledButton* startButton = new StyledButton("Ingresar");


    QWidget *container = new QWidget();
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(textLabel);
    hLayout->addWidget(nameInput);
    hLayout->addWidget(startButton);
    container->setLayout(hLayout);
    container->setStyleSheet("background: transparent;");

    QGraphicsProxyWidget *proxy = addWidget(container);
    proxy->setPos(120, 200);
    connect(startButton, &QPushButton::clicked, this, [this]() {
        emit startClicked(nameInput->text());
    });
}
