#include "map_serializer.h"
#include <yaml-cpp/yaml.h>
#include <QGraphicsPixmapItem>
#include <QFile>
#include <QTextStream>
#include <QDebug>

void MapSerializer::saveToYaml(QGraphicsScene* scene, const QString& filePath) {
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "map" << YAML::Value;
    out << YAML::BeginMap;
    out << YAML::Key << "tiles" << YAML::Value << YAML::BeginSeq;

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

        out << YAML::BeginMap;
        out << YAML::Key << "x" << YAML::Value << x;
        out << YAML::Key << "y" << YAML::Value << y;
        out << YAML::Key << "type" << YAML::Value << type.toStdString();
        out << YAML::Key << "asset" << YAML::Value << assetPath.toStdString();
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
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("No se pudo abrir el archivo YAML.");
        return;
    }

    YAML::Node root = YAML::Load(file.readAll().toStdString());
    file.close();

    for (QGraphicsItem* item : scene->items()) {
        if (auto pix = dynamic_cast<QGraphicsPixmapItem*>(item)) {
            scene->removeItem(pix);
            delete pix;
        }
    }

    if (!root["map"] || !root["map"]["tiles"]) return;

    for (const auto& tile : root["map"]["tiles"]) {
        int x = tile["x"].as<int>();
        int y = tile["y"].as<int>();
        std::string path = tile["asset"].as<std::string>();
        if (!tile["asset"]) {
            qWarning() << "El nodo no contiene 'path'";
            continue;
        }
        QPixmap pix(QString::fromStdString(path));
        if (pix.isNull()) continue;

        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pix);
        item->setPos(x * 32, y * 32);
        item->setData(0, QString::fromStdString(path));
        scene->addItem(item);
    }
}