#include "welcome_scene.h"

#include <QGraphicsProxyWidget>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QVBoxLayout>

#include "styled_button.h"

WelcomeScene::WelcomeScene(QObject *parent) : QGraphicsScene(parent) {
    setUpWelcome();
}

void WelcomeScene::setUpWelcome() {
    QGraphicsPixmapItem* backround = new QGraphicsPixmapItem(QPixmap("client/lobby/assets/welcome.jpg").scaled(640, 400));
    addItem(backround);
    QPixmap logo("client/lobby/assets/logo.png");
    logo = logo.scaledToHeight(100, Qt::SmoothTransformation);
    QGraphicsPixmapItem* logoItem = addPixmap(logo);
    logoItem->setPos(120, 70);

    QLabel *textLabel = new QLabel("¡Bienvenido!");
    textLabel->setStyleSheet("QLabel { color: white; font-size: 16px; font-weight: bold; }");

    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Ingrese su username");
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

    ipInput = new QLineEdit();
    ipInput->setPlaceholderText("IP del servidor");
    ipInput->setFixedWidth(180);
    ipInput->setStyleSheet(R"(
        QLineEdit {
            background-color: rgba(255, 255, 255, 0.9);
            color: #000000;
            border: 1px solid #cccccc;
            border-radius: 6px;
            padding: 4px;
        }
    )");

    portInput = new QLineEdit();
    portInput->setPlaceholderText("Puerto");
    portInput->setFixedWidth(180);
    portInput->setStyleSheet(R"(
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
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(textLabel);
    vLayout->addWidget(nameInput);
    vLayout->addWidget(ipInput);
    vLayout->addWidget(portInput);
    vLayout->addWidget(startButton);
    container->setLayout(vLayout);
    container->setStyleSheet("background: transparent;");

    QGraphicsProxyWidget *proxy = addWidget(container);
    proxy->setPos(15, 200);
    connect(startButton, &QPushButton::clicked, this, [this]() {
        emit startClicked(nameInput->text(), ipInput->text(), portInput->text());
    });

    connect(this, &QGraphicsScene::sceneRectChanged, this, [this, backround, logoItem, proxy](const QRectF &rect) {
        backround->setPixmap(QPixmap("client/lobby/assets/welcome.jpg").scaled(rect.width(), rect.height()));
        
        qreal scale = rect.width() / 640.0;
        logoItem->setPos(120 * scale, 70 * scale);
        
        proxy->setPos(15 * scale, 200 * scale);
    });
}
