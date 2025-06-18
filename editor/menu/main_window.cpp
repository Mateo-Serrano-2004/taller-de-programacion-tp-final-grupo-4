#include "main_window.h"

#include <QMessageBox>
#include <QVBoxLayout>

#include "../scenes/menu_widget.h"

#include "ui_main_window.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    setUpWindow();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setUpWindow() {
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setStyleSheet("background: #222222;");
    showMenuScene();
}

void MainWindow::showMenuScene() {
    MenuWidget* menuWidget = new MenuWidget(this);
    setCentralWidget(menuWidget);

    connect(menuWidget, &MenuWidget::createMapRequested, this, [this]() {
        mapEditor = new MapEditorWidget(this);
        connect(mapEditor, &MapEditorWidget::backClicked, this, &MainWindow::showMenuScene,
                Qt::QueuedConnection);
        setCentralWidget(mapEditor);
    });

    connect(menuWidget, &MenuWidget::editMapRequested, this, [this](const QString& filePath) {
        mapEditor = new MapEditorWidget(this);
        connect(mapEditor, &MapEditorWidget::backClicked, this, &MainWindow::showMenuScene,
                Qt::QueuedConnection);

        mapEditor->loadMap(filePath);
        setCentralWidget(mapEditor);
    });
}
