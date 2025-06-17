#include "join_game_scene.h"

#include <QHeaderView>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QWidget>
#include <vector>

#include "../widgets/styled_button.h"

JoinGameScene::JoinGameScene(QObject* parent): BackgroundScene(parent), mainWidgetProxy(nullptr) {
    setUpJoin();
}

void JoinGameScene::setAvailableGames(const std::vector<DTO::GameInfoDTO>& games) {
    gameTableWidget->setRowCount(static_cast<int>(games.size()));
    int row = 0;
    for (const auto& game: games) {
        QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(game.name));
        QTableWidgetItem* playersItem = new QTableWidgetItem(
                QString("%1/%2").arg(game.current_players).arg(game.max_players));
        QTableWidgetItem* mapItem = new QTableWidgetItem(QString::fromStdString(game.map_name));
        nameItem->setData(Qt::UserRole, static_cast<int>(game.id));
        gameTableWidget->setItem(row, 0, nameItem);
        gameTableWidget->setItem(row, 1, playersItem);
        gameTableWidget->setItem(row, 2, mapItem);
        row++;
    }
    gameTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    gameTableWidget->setColumnWidth(0, 250);
    gameTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    gameTableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
}

int JoinGameScene::selectedGameId() const {
    int row = gameTableWidget->currentRow();
    if (row >= 0) {
        return gameTableWidget->item(row, 0)->data(Qt::UserRole).toInt();
    }
    return -1;
}

void JoinGameScene::resizeScene(const QSizeF& size) {
    if (mainWidgetProxy) {
        QPointF centerPos((size.width() - mainWidgetProxy->size().width()) / 2,
                          (size.height() - mainWidgetProxy->size().height()) / 2);
        mainWidgetProxy->setPos(centerPos);
    }
}

void JoinGameScene::setUpJoin() {
    QLabel* title = new QLabel("Partidas disponibles:");
    title->setStyleSheet("color: white; font-size: 16px; font-weight: bold;");

    gameTableWidget = new QTableWidget();
    gameTableWidget->setColumnCount(3);
    QStringList headers = {"Nombre", "Jugadores", "Mapa"};
    gameTableWidget->setHorizontalHeaderLabels(headers);
    gameTableWidget->horizontalHeader()->setStretchLastSection(true);
    gameTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    gameTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    gameTableWidget->setShowGrid(false);
    gameTableWidget->setStyleSheet(
            "QTableWidget { background: transparent; color: white; font-family: monospace; }");
    gameTableWidget->verticalHeader()->setVisible(false);
    gameTableWidget->horizontalHeader()->setHighlightSections(false);

    joinButton = new StyledButton("Unirse");
    StyledButton* refreshButton = new StyledButton("Refresh");
    joinButton->setFixedWidth(100);
    refreshButton->setFixedWidth(100);
    joinButton->setEnabled(false);

    QWidget* buttonRow = new QWidget();
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->setSpacing(10);
    buttonLayout->addWidget(joinButton);
    buttonLayout->addWidget(refreshButton);
    buttonRow->setLayout(buttonLayout);
    buttonRow->setStyleSheet("background: transparent;");

    QWidget* container = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(title);
    layout->addWidget(gameTableWidget);
    layout->addWidget(buttonRow);
    container->setLayout(layout);
    container->setFixedWidth(500);
    container->setStyleSheet("background: transparent; color: white;");

    mainWidgetProxy = addWidget(container);
    resizeScene(sceneRect().size());

    connect(gameTableWidget, &QTableWidget::itemSelectionChanged, this,
            [this]() { joinButton->setEnabled(gameTableWidget->currentRow() >= 0); });

    connect(joinButton, &QPushButton::clicked, this, [this]() {
        int row = gameTableWidget->currentRow();
        if (row >= 0) {
            emit joinRequestedGame(gameTableWidget->item(row, 0)->text());
        }
    });
    connect(refreshButton, &QPushButton::clicked, this, &JoinGameScene::refreshClicked);

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
    connect(backButton, &QPushButton::clicked, this, &JoinGameScene::backClicked);
}
