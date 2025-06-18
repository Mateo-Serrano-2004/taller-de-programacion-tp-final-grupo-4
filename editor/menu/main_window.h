#ifndef EDITOR_MAIN_WINDOW_H
#define EDITOR_MAIN_WINDOW_H

#include <QMainWindow>

#include "../scenes/map_editor_widget.h"

namespace Ui {
class MainWindow;
}

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void setUpWindow();
    void showMenuScene();

private:
    Ui::MainWindow* ui;
    MapEditorWidget* mapEditor = nullptr;
};

#endif  // EDITOR_MAIN_WINDOW_H
