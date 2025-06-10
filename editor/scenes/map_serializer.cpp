#include "map_serializer.h"
#include <yaml-cpp/yaml.h>
#include <QGraphicsPixmapItem>
#include <QFile>
#include <algorithm>
#include <QTextStream>
#include <QDebug>
#include <vector>

void MapSerializer::saveToYaml(QGraphicsScene* scene, const QString& filePath) {
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "map" << YAML::Value;
    out << YAML::BeginMap;
    out << YAML::Key << "tiles" << YAML::Value << YAML::BeginSeq;

    struct Tile {
        int x, y;
        QString type;
        QString asset;
    };

    std::vector<Tile> tiles;

    for (QGraphicsItem* item : scene->items()) {
        auto pixItem = dynamic_cast<QGraphicsPixmapItem*>(item);
        if (!pixItem) continue;

        QPointF pos = pixItem->pos();
        int x = static_cast<int>(pos.x()) / 32;
        int y = static_cast<int>(pos.y()) / 32;

        QString assetPath = pixItem->data(0).toString();
        if (assetPath.isEmpty()) continue;

        QString type;
        if (assetPath.contains("/Walls/")) type = "wall";
        else if (assetPath.contains("/Backgrounds/")) type = "background";
        else if (assetPath.contains("/Boxes/")) type = "box";
        else if (assetPath.contains("/Sites/")) type = "site";
        else if (assetPath.contains("/Cars/")) type = "car";
        else type = "unknown";

        tiles.push_back({x, y, type, assetPath});
        /*
        out << YAML::BeginMap;
        out << YAML::Key << "x" << YAML::Value << x;
        out << YAML::Key << "y" << YAML::Value << y;
        out << YAML::Key << "type" << YAML::Value << type.toStdString();
        out << YAML::Key << "asset" << YAML::Value << assetPath.toStdString();
        out << YAML::EndMap;*/
    }
    //sorted tiles by y then by x
    std::sort(tiles.begin(), tiles.end(), [](const Tile& a, const Tile& b) {
        if (a.y == b.y) return a.x < b.x;
        return a.y < b.y;
    });

    for (const auto& tile : tiles) {
        out << YAML::BeginMap;
        out << YAML::Key << "x" << YAML::Value << tile.x;
        out << YAML::Key << "y" << YAML::Value << tile.y;
        out << YAML::Key << "type" << YAML::Value << tile.type.toStdString();
        out << YAML::Key << "asset" << YAML::Value << tile.asset.toStdString();
        out << YAML::EndMap;
    }

    out << YAML::EndSeq;
    out << YAML::EndMap;
    out << YAML::EndMap;

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << out.c_str();
        file.close();
    }
}

void MapSerializer::loadFromYaml(const QString& filePath, QGraphicsScene* scene) {
    scene->clear();
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("No se pudo abrir el archivo YAML.");
        return;
    }

    YAML::Node root = YAML::LoadFile(filePath.toStdString());
    std::map<QString, QList <YAML::Node>> groupedTiles;


    for (const auto& tile : root["map"]["tiles"]) {
        QString type = QString::fromStdString(tile["type"].as<std::string>());
        groupedTiles[type].append(tile);
    }

    QStringList orderedLayers = {"background", "wall", "box", "site", "car", "unknown"};

    for (const QString& layer : orderedLayers) {
        for (const auto& tile : groupedTiles[layer]) {
            int x = tile["x"].as<int>();
            int y = tile["y"].as<int>();
            QString assetPath = QString::fromStdString(tile["asset"].as<std::string>());

            QPixmap pix(assetPath);
            if (pix.isNull()) {
                qWarning() << "No se pudo cargar imagen:" << assetPath;
                continue;
            }

            QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pix);
            pixmapItem->setPos(x * 32, y * 32);
            pixmapItem->setData(0, assetPath);
            scene->addItem(pixmapItem);
        }
        
    }
}