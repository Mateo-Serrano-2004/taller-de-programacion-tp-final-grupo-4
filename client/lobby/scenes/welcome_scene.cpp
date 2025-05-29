#include "welcome_scene.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>
#include <QVBoxLayout>

#include "../widgets/styled_button.h"
#include "../widgets/styled_line_edit.h"

WelcomeScene::WelcomeScene(QObject* parent): BackgroundScene(parent) { setUpWelcome(); }

void WelcomeScene::setUpWelcome() {
    QPixmap logo("client/lobby/assets/logo.png");
    logo = logo.scaledToHeight(100, Qt::SmoothTransformation);
    QGraphicsPixmapItem* logoItem = addPixmap(logo);
    logoItem->setPos(120, 70);

    QLabel* textLabel = new QLabel("¡Bienvenido!");
    textLabel->setStyleSheet("QLabel { color: white; font-size: 16px; font-weight: bold; }");

    nameInput = new StyledLineEdit();
    nameInput->setPlaceholderText("Ingrese su username");

    ipInput = new StyledLineEdit();
    ipInput->setPlaceholderText("IP del servidor");

    portInput = new StyledLineEdit();
    portInput->setPlaceholderText("Puerto");

    StyledButton* startButton = new StyledButton("Ingresar");

    QWidget* container = new QWidget();
    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->addWidget(textLabel);
    vLayout->addWidget(nameInput);
    vLayout->addWidget(ipInput);
    vLayout->addWidget(portInput);
    vLayout->addWidget(startButton);
    container->setLayout(vLayout);
    container->setStyleSheet("background: transparent;");

    QGraphicsProxyWidget* proxy = addWidget(container);
    proxy->setPos(15, 200);

    auto showError = [this](const QString& message) {
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

        if (!views().isEmpty()) {
            QGraphicsView* view = views().first();
            QPoint center = view->mapToGlobal(view->viewport()->rect().center());
            msgBox.move(center.x() - msgBox.width() / 2, center.y() - msgBox.height() / 2);
        }

        msgBox.exec();
    };

    connect(startButton, &QPushButton::clicked, this, [this, showError]() {
        QString username = nameInput->text().trimmed();
        QString ip = ipInput->text().trimmed();
        QString port = portInput->text().trimmed();

        if (username.isEmpty() || ip.isEmpty() || port.isEmpty()) {
            showError("Por favor, complete todos los campos.");
            return;
        }

        bool ok;
        int portNumber = port.toInt(&ok);
        if (!ok || portNumber <= 0 || portNumber > 65535) {
            showError("El puerto debe ser un número válido entre 1 y 65535.");
            return;
        }

        emit startClicked(username, ip, port);
    });

    connect(this, &QGraphicsScene::sceneRectChanged, this,
            [this, logoItem, proxy](const QRectF& rect) {
                qreal scale = rect.width() / 640.0;
                logoItem->setPos(120 * scale, 70 * scale);

                proxy->setPos(15 * scale, 200 * scale);
            });
}
