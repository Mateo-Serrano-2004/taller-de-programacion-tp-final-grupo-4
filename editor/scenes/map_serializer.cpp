#include "map_serializer.h"

#include <QDebug>
#include <QFile>
#include <QGraphicsPixmapItem>
#include <QIcon>
#include <QListWidgetItem>
#include <QTextStream>
#include <limits>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "common/asset_addresser.h"
#include "common/definitions.h"

#include "constants.h"

void MapSerializer::saveToYaml(QGraphicsScene* scene, const QString& filePath) {
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "map" << YAML::Value;
    out << YAML::BeginMap;

    struct Tile {
        int x, y;
        QString name;
        QString type;
    };

    std::vector<Tile> tiles;
    int minX = std::numeric_limits<int>::max();
    int minY = std::numeric_limits<int>::max();
    int maxX = 0, maxY = 0;

    for (QGraphicsItem* item: scene->items()) {
        auto tileItem = dynamic_cast<QGraphicsPixmapItem*>(item);
        if (!tileItem)
            continue;

        QPointF pos = tileItem->pos();
        int x = static_cast<int>(pos.x()) / TILE_SIZE;
        int y = static_cast<int>(pos.y()) / TILE_SIZE;


        QString name = tileItem->data(0).toString();
        QString type = tileItem->data(1).toString();
        if (type.isEmpty() || name.isEmpty())
            continue;

        tiles.push_back(Tile{x, y, name, type});

        if (x > maxX)
            maxX = x;
        if (y > maxY)
            maxY = y;
        if (x < minX)
            minX = x;
        if (y < minY)
            minY = y;
    }

    out << YAML::Key << "minWidth" << YAML::Value << (minX);
    out << YAML::Key << "maxWidth" << YAML::Value << (maxX);
    out << YAML::Key << "minHeight" << YAML::Value << (minY);
    out << YAML::Key << "maxHeight" << YAML::Value << (maxY);
    out << YAML::EndMap;
    out << YAML::Key << "tiles" << YAML::Value << YAML::BeginSeq;

    for (const auto& tile: tiles) {
        out << YAML::BeginMap;
        out << YAML::Key << "x" << YAML::Value << tile.x;
        out << YAML::Key << "y" << YAML::Value << tile.y;
        out << YAML::Key << "name" << YAML::Value << tile.name.toStdString();
        out << YAML::Key << "type" << YAML::Value << tile.type.toStdString();
        out << YAML::EndMap;
    }

    out << YAML::EndSeq;
    out << YAML::EndMap;


    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << out.c_str();
        file.close();
    }
}

void MapSerializer::loadFromYaml(const QString& filePath, QGraphicsScene* scene) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("No se pudo abrir el archivo YAML.");
        return;
    }

    YAML::Node root = YAML::LoadFile(filePath.toStdString());
    Model::AssetAddresser addresser;

    for (const auto& tile: root["tiles"]) {
        int x = tile["x"].as<int>();
        int y = tile["y"].as<int>();
        QString name = QString::fromStdString(tile["name"].as<std::string>());
        QString type = QString::fromStdString(tile["type"].as<std::string>());

        QListWidgetItem tempItem;
        tempItem.setData(Qt::UserRole, name);
        tempItem.setData(Qt::UserRole + 1, type);
        tempItem.setIcon(QIcon(QString::fromStdString(addresser.get_tile_path(type.toStdString())) +
                               "/" + name));

        QIcon icon = tempItem.icon();
        QPixmap pixmap = icon.pixmap(TILE_SIZE, TILE_SIZE);
        if (pixmap.isNull()) {
            qWarning() << "No se pudo cargar imagen:" << name;
            continue;
        }
        QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap);
        pixmapItem->setPos(x * TILE_SIZE, y * TILE_SIZE);
        pixmapItem->setData(0, tempItem.data(Qt::UserRole).toString());
        pixmapItem->setData(1, tempItem.data(Qt::UserRole + 1).toString());
        scene->addItem(pixmapItem);
    }
}
