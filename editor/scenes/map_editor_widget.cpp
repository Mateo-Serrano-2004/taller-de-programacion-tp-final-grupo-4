#include "map_editor_widget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QMessageBox>
#include <QLabel>
#include <QDir>
#include <QIcon>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QFileDialog>
#include "map_serializer.h"

#include "../widgets/styled_button.h"
#include "grid_view.h"
#include "../widgets/styled_file_dialog.h"

void MapEditorWidget::setUpLeftPanel() {
    leftPanel = new QWidget(this);
    leftPanel->setFixedWidth(170);
    QVBoxLayout* leftLayout = new QVBoxLayout(leftPanel);
    backButton = new StyledButton("Volver", leftPanel);
    saveButton = new StyledButton("Guardar", leftPanel);
    leftLayout->addWidget(backButton);
    leftLayout->addWidget(saveButton);
    leftLayout->addStretch();
    leftPanel->setLayout(leftLayout);
    leftPanel->setStyleSheet("background: #222222;");
}  

void MapEditorWidget::setUpRightPanel() {
    rightPanel = new QWidget(this);
    rightPanel->setFixedWidth(250);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);
    QLabel* assetsTitle = new QLabel("<b>Assets</b>", rightPanel);
    assetsTitle->setStyleSheet("color: white; margin-bottom: 8px;");
    assetsList = new QListWidget(rightPanel);
    rightLayout->addWidget(assetsTitle);
    rightLayout->addWidget(assetsList);
    rightPanel->setLayout(rightLayout);
    rightPanel->setStyleSheet("background: #222222;");

    assetsList->setDragEnabled(true);
    assetsList->setSelectionMode(QAbstractItemView::SingleSelection);
    assetsList->setFocusPolicy(Qt::StrongFocus);
    assetsList->installEventFilter(this);

    assetsList->viewport()->installEventFilter(this);
}

MapEditorWidget::MapEditorWidget(QWidget* parent) : QWidget(parent) {
    setUpLeftPanel();
    setUpRightPanel();
    setUpGrid();
    loadAssets();

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(leftPanel);
    mainLayout->addWidget(gridView, 1);
    mainLayout->addWidget(rightPanel);
    setLayout(mainLayout);

    connect(backButton, &QPushButton::clicked, this, [this]() {
        QMessageBox msgBox(QMessageBox::Question, "Confirmar", "¿Estás seguro que quieres volver?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setStyleSheet("QPushButton { min-width: 80px; min-height: 30px; }");
        if (msgBox.exec() == QMessageBox::Yes) emit backClicked();
    });

    connect(saveButton, &QPushButton::clicked, this, [this]() {
        StyledFileDialog fileDialog(this);
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
        fileDialog.setNameFilter("YAML files (*.yaml *.yml)");
        fileDialog.setWindowTitle("Guardar mapa");

        if (fileDialog.exec() == QDialog::Accepted) {
            QString filePath = fileDialog.selectedFiles().first();
            if (!filePath.endsWith(".yaml") && !filePath.endsWith(".yml"))
                filePath += ".yaml";

            MapSerializer::saveToYaml(gridScene, filePath);
        }
        
    });


    selectedAsset = -1;
    connect(assetsList, &QListWidget::itemClicked, this, [this](QListWidgetItem* item) {
        if (item->flags() & Qt::ItemIsSelectable) {
            selectedAsset = assetsList->row(item);
        }
    });

    connect(static_cast<GridView*>(gridView), &GridView::cellClicked, this, [this](int x, int y, Qt::MouseButton button) {
        if (button == Qt::RightButton) {
            removeTileAt(x, y);
            assetsList->clearSelection();
            selectedAsset = -1;
            return;
        }
        
        if (selectedAsset < 0) return;
        QListWidgetItem* item = assetsList->item(selectedAsset);
        placeTileAt(x, y, item);
    });

    connect(static_cast<GridView*>(gridView), &GridView::cellDropped, this, [this](int x, int y, int assetIndex) {
        if (assetIndex < 0) return;
        QListWidgetItem* item = assetsList->item(assetIndex);
        placeTileAt(x, y, item);
    });
}

void MapEditorWidget::setUpGrid() {
    gridScene = new QGraphicsScene(this);
    int tile = 32;
    int cols = 50;
    int rows = 50; 
    int gridW = cols * tile;
    int gridH = rows * tile;

    gridScene->addRect(0, 0, gridW, gridH, QPen(Qt::NoPen), QBrush(Qt::white));
    QPen gridPen(QColor("#222222"));
    for (int x = 0; x <= gridW; x += tile)
        gridScene->addLine(x, 0, x, gridH, gridPen);
    for (int y = 0; y <= gridH; y += tile)
        gridScene->addLine(0, y, gridW, y, gridPen);

    gridView = new GridView(gridScene, this);
}

void MapEditorWidget::addCategory(const QString& title, const QString& path, const QString& type) {
    QListWidgetItem* titleItem = new QListWidgetItem(title);
    titleItem->setBackground(QBrush(QColor("#222222")));
    QFont titleFont = titleItem->font();
    titleFont.setBold(true);
    titleItem->setFont(titleFont);
    titleItem->setFlags(Qt::NoItemFlags);
    assetsList->addItem(titleItem);

    QDir dir(path);
    QStringList files = dir.entryList(QStringList() << "*.png", QDir::Files);
    for (const QString& fileName : files) {
        QListWidgetItem* item = new QListWidgetItem(QIcon(dir.filePath(fileName)), fileName);
        item->setData(Qt::UserRole, type);
        item->setData(Qt::UserRole + 1, dir.filePath(fileName)); //here we save the full asset path

        assetsList->addItem(item);
    }
}

void MapEditorWidget::loadAssets() {
    assetsList->clear();
    assetsList->setStyleSheet("background: #FFFFFF;");

    addCategory("Backgrounds", "assets/gfx/tiles/Backgrounds", "background");
    addCategory("Walls", "assets/gfx/tiles/Walls", "wall");
    addCategory("Boxes", "assets/gfx/tiles/Boxes", "box");
    addCategory("Sites", "assets/gfx/tiles/Sites", "site");
    addCategory("Cars", "assets/gfx/tiles/Cars", "car");
}

void MapEditorWidget::removeTileAt(int x, int y) {
    for (QGraphicsItem* item : gridScene->items(QRectF(x*32, y*32, 32, 32))) {
        if (auto pix = dynamic_cast<QGraphicsPixmapItem*>(item)) {
            if (pix->pos() == QPointF(x*32, y*32)) {
                gridScene->removeItem(pix);
                delete pix;
                break;
            }
        }
    }
}

void MapEditorWidget::placeTileAt(int x, int y, QListWidgetItem* item) {
    if (!(item->flags() & Qt::ItemIsSelectable)) return;
    QIcon icon = item->icon();
    QPixmap pixmap = icon.pixmap(32, 32);
    removeTileAt(x, y);
    QGraphicsPixmapItem* tileItem = new QGraphicsPixmapItem(pixmap);
    tileItem->setPos(x * 32, y * 32);

    //save asset path in the item data
    tileItem->setData(0, item->data(Qt::UserRole + 1));

    gridScene->addItem(tileItem);
}

bool MapEditorWidget::eventFilter(QObject* obj, QEvent* event) {
    if (obj == assetsList->viewport()) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                QListWidgetItem* item = assetsList->itemAt(mouseEvent->pos());
                if (item && (item->flags() & Qt::ItemIsSelectable)) {
                    dragStartPos = mouseEvent->pos();
                }
            }
        } else if (event->type() == QEvent::MouseMove) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (!(mouseEvent->buttons() & Qt::LeftButton)) return false;
            if (dragStartPos.isNull()) return false;

            if ((mouseEvent->pos() - dragStartPos).manhattanLength() >= QApplication::startDragDistance()) {
                QListWidgetItem* item = assetsList->itemAt(dragStartPos);
                if (item && (item->flags() & Qt::ItemIsSelectable)) {
                    QDrag* drag = new QDrag(assetsList);
                    QMimeData* mimeData = new QMimeData;
                    mimeData->setData("application/x-asset-index", QByteArray::number(assetsList->row(item)));
                    drag->setMimeData(mimeData);
                    
                    QPixmap pixmap = item->icon().pixmap(32, 32);
                    drag->setPixmap(pixmap);
                    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
                    
                    Qt::DropAction dropAction = drag->exec(Qt::CopyAction);
                    if (dropAction == Qt::CopyAction) {
                        selectedAsset = assetsList->row(item);
                    }
                    dragStartPos = QPoint();
                    return true;
                }
            }
        } else if (event->type() == QEvent::MouseButtonRelease) {
            dragStartPos = QPoint();
        }
    }
    return QWidget::eventFilter(obj, event);
} 

void MapEditorWidget::loadMap(const QString& path) {
    MapSerializer::loadFromYaml(path, gridScene);
}
