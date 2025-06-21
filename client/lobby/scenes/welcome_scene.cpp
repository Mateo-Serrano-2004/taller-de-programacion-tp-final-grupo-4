#include "welcome_scene.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

#include "../widgets/styled_button.h"
#include "../widgets/styled_line_edit.h"
#include "../widgets/error_dialog.h"

WelcomeScene::WelcomeScene(QObject* parent): BackgroundScene(parent) { setUpWelcome(); }

void WelcomeScene::setUpWelcome() {
    QPixmap logo(":/assets/logo.png");
    logo = logo.scaledToHeight(100, Qt::SmoothTransformation);
    QGraphicsPixmapItem* logoItem = addPixmap(logo);
    logoItem->setPos(120, 70);

    QLabel* textLabel = new QLabel("¡Bienvenido!");
    textLabel->setStyleSheet(R"(
        QLabel { 
            color: #ecf0f1; 
            font-size: 16px; 
            font-weight: bold; 
            margin-bottom: 10px;
        }
    )");
    textLabel->setAlignment(Qt::AlignLeft);

    nameInput = new StyledLineEdit();
    nameInput->setPlaceholderText("Ingrese su username");
    nameInput->setFixedSize(200, 30);

    ipInput = new StyledLineEdit();
    ipInput->setPlaceholderText("IP del servidor");
    ipInput->setFixedSize(200, 30);

    portInput = new StyledLineEdit();
    portInput->setPlaceholderText("Puerto");
    portInput->setFixedSize(200, 30);

    StyledButton* startButton = new StyledButton("Ingresar");
    startButton->setFixedSize(200, 35);

    QWidget* container = new QWidget();
    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->addWidget(textLabel);
    vLayout->addWidget(nameInput);
    vLayout->addWidget(ipInput);
    vLayout->addWidget(portInput);
    vLayout->addWidget(startButton);
    vLayout->setAlignment(Qt::AlignLeft);
    vLayout->setSpacing(10);
    vLayout->setContentsMargins(10, 10, 10, 10);
    container->setLayout(vLayout);
    container->setFixedWidth(220);
    container->setStyleSheet("background: transparent;");

    QGraphicsProxyWidget* proxy = addWidget(container);
    proxy->setPos(10, 180);

    connect(startButton, &QPushButton::clicked, this, [this]() {
        QString username = nameInput->text().trimmed();
        QString ip = ipInput->text().trimmed();
        QString port = portInput->text().trimmed();

        if (username.isEmpty() || ip.isEmpty() || port.isEmpty()) {
            ErrorDialog::showError("Por favor, complete todos los campos.", this);
            return;
        }

        if (username.length() > 10) {
            ErrorDialog::showError("El nombre de usuario no puede tener más de 10 caracteres.", this);
            return;
        }

        bool ok;
        int portNumber = port.toInt(&ok);
        if (!ok || portNumber <= 0 || portNumber > 65535) {
            ErrorDialog::showError("El puerto debe ser un número válido entre 1 y 65535.", this);
            return;
        }

        emit startClicked(username, ip, port);
    });

    connect(this, &QGraphicsScene::sceneRectChanged, this,
            [this, logoItem, proxy](const QRectF& rect) {
                qreal scale = rect.width() / 640.0;
                logoItem->setPos(120 * scale, 70 * scale);

                proxy->setPos(10 * scale, 180 * scale);
            });
}
