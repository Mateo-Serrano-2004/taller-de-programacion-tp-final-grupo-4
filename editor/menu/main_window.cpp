#include "main_window.h"

#include "ui_main_window.h"

#include <QVBoxLayout>
#include <QMessageBox>

#include "../scenes/menu_widget.h"
#include "../scenes/map_editor_widget.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    setUpWindow();
}   

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setUpWindow() {
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setStyleSheet("background: #222222;");
    showMenuScene();
}

void MainWindow::showMenuScene() {
    MenuWidget* menuWidget = new MenuWidget(this);
    setCentralWidget(menuWidget);
    connect(menuWidget, &MenuWidget::createMapRequested, this, &MainWindow::showMapEditorScene, Qt::QueuedConnection);
    connect(menuWidget, &MenuWidget::editMapRequested, this, &MainWindow::showMapEditorSceneWithMap, Qt::QueuedConnection);
}

void MainWindow::showMapEditorScene() {
    MapEditorWidget* editorWidget = new MapEditorWidget(this);
    setCentralWidget(editorWidget);
    connect(editorWidget, &MapEditorWidget::backClicked, this, &MainWindow::showMenuScene, Qt::QueuedConnection);
}

void MainWindow::showMapEditorSceneWithMap(const QString& filePath) {
    MapEditorWidget* editorWidget = new MapEditorWidget(this);
    setCentralWidget(editorWidget);
    connect(editorWidget, &MapEditorWidget::backClicked, this, &MainWindow::showMenuScene, Qt::QueuedConnection);
}
