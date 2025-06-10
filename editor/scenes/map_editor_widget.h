#ifndef MAP_EDITOR_WIDGET_H
#define MAP_EDITOR_WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QListWidget>
#include <QPushButton>

class MapEditorWidget : public QWidget {
    Q_OBJECT
public:
    explicit MapEditorWidget(QWidget* parent = nullptr);
    void loadMap(const QString& filePath);

signals:
    void backClicked();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    void setUpLeftPanel();
    void setUpRightPanel();
    void setUpGrid();
    void loadAssets();
    void addCategory(const QString& title, const QString& path, const QString& type);
    void removeTileAt(int x, int y);
    void placeTileAt(int x, int y, QListWidgetItem* item);
    void drawGridLines(int width, int height);
    QWidget* leftPanel = nullptr;
    QGraphicsView* gridView = nullptr;
    QGraphicsScene* gridScene = nullptr;
    QWidget* rightPanel = nullptr;
    QListWidget* assetsList = nullptr;
    QPushButton* backButton = nullptr;
    QPushButton* saveButton = nullptr;
    QPoint dragStartPos;
    int selectedAsset = -1;
};

#endif // MAP_EDITOR_WIDGET_H 