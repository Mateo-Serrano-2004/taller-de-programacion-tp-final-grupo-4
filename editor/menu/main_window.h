#ifndef EDITOR_MAIN_WINDOW_H
#define EDITOR_MAIN_WINDOW_H

#include <QMainWindow>

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
    void showMapEditorScene();
    void showMapEditorSceneWithMap(const QString& filePath);

private:
    Ui::MainWindow* ui;
};

#endif  // EDITOR_MAIN_WINDOW_H
