#include "game_creation_scene.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QGraphicsProxyWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#include "../widgets/error_dialog.h"
#include "../widgets/styled_button.h"

GameCreationScene::GameCreationScene(QObject* parent):
        BackgroundScene(parent), mapListWidget(new QListWidget), gameNameInput(new QLineEdit) {
    setUpGameCreation();
}

void GameCreationScene::setAvailableMaps(const QStringList& maps) {
    mapListWidget->clear();
    mapListWidget->addItems(maps);
    if (!maps.isEmpty()) {
        mapListWidget->setCurrentRow(0);
    }
}

void GameCreationScene::centerWidget(QGraphicsProxyWidget* proxy) {
    QRectF sceneBounds = sceneRect();
    QSizeF widgetSize = proxy->size();
    QPointF centerPos((sceneBounds.width() - widgetSize.width()) / 2,
                      (sceneBounds.height() - widgetSize.height()) / 2);
    proxy->setPos(centerPos);
}

GameCreationScene::~GameCreationScene() {
    if (mapListWidget) {
        delete mapListWidget;
    }
    if (gameNameInput) {
        delete gameNameInput;
    }
    if (createButton) {
        delete createButton;
    }
}

bool GameCreationScene::isValidGameName(const QString& name) { return !name.trimmed().isEmpty(); }

void GameCreationScene::updateCreateButtonState() {
    bool hasValidName = isValidGameName(gameNameInput->text());
    bool hasMap = mapListWidget->currentItem() != nullptr;
    createButton->setEnabled(hasValidName && hasMap);
}

void GameCreationScene::setUpGameCreation() {
    QLabel* mapLabel = new QLabel("Seleccioná un mapa:");
    mapLabel->setStyleSheet("color: white; font-weight: bold; font-size: 14px;");

    QLabel* nameLabel = new QLabel("Nombre de la partida:");
    nameLabel->setStyleSheet("color: white; font-weight: bold; font-size: 14px;");

    gameNameInput->setPlaceholderText("Inserte el nombre de la partida");
    gameNameInput->setStyleSheet(
            "border: 2px solid rgba(255, 255, 255, 0.4); border-radius: 5px; padding: 5px;");

    mapListWidget->setStyleSheet("border: 2px solid rgba(255, 255, 255, 0.4); border-radius: 5px;");

    createButton = new StyledButton("Crear");
    createButton->setEnabled(false);

    QPushButton* backButton = new StyledButton("Volver");
    backButton->setFixedWidth(80);
    QWidget* backContainer = new QWidget();
    QHBoxLayout* backLayout = new QHBoxLayout();
    backLayout->setContentsMargins(0, 0, 0, 0);
    backLayout->setSpacing(0);
    backLayout->addWidget(backButton);
    backContainer->setLayout(backLayout);
    backContainer->setStyleSheet("background: transparent;");
    QGraphicsProxyWidget* backProxy = addWidget(backContainer);
    backProxy->setPos(10, 10);
    connect(backButton, &QPushButton::clicked, this, &GameCreationScene::backClicked);

    QWidget* container = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout;

    mainLayout->addWidget(mapLabel);
    mainLayout->addWidget(mapListWidget);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(gameNameInput);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(createButton);
    container->setLayout(mainLayout);
    container->setStyleSheet("background: transparent; color: white;");
    container->setFixedWidth(300);

    QGraphicsProxyWidget* proxy = addWidget(container);
    centerWidget(proxy);

    connect(gameNameInput, &QLineEdit::textChanged, this,
            &GameCreationScene::updateCreateButtonState);

    connect(mapListWidget, &QListWidget::itemSelectionChanged, this,
            &GameCreationScene::updateCreateButtonState);

    connect(createButton, &QPushButton::clicked, this, [this]() {
        QString gameName = gameNameInput->text().trimmed();
        QListWidgetItem* selectedItem = mapListWidget->currentItem();

        if (!isValidGameName(gameName)) {
            ErrorDialog::showError("Por favor, ingresa un nombre válido para la partida.", this);
            gameNameInput->setFocus();
            return;
        }

        if (!selectedItem) {
            ErrorDialog::showError("Por favor, selecciona un mapa.", this);
            return;
        }

        emit createGameRequested(gameName, selectedItem->text());
    });
}
