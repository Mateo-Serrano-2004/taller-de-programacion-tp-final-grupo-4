#include "map_serializer.h"
#include <yaml-cpp/yaml.h>
#include <QGraphicsPixmapItem>
#include <QFile>
#include <QTextStream>

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
