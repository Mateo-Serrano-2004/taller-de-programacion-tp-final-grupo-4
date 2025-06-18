#ifndef MAP_SERIALIZER_H
#define MAP_SERIALIZER_H

#include <QGraphicsScene>
#include <QString>

class MapSerializer {
public:
    static void saveToYaml(QGraphicsScene* scene, const QString& filePath);
    static void loadFromYaml(const QString& filePath, QGraphicsScene* scene);
};

#endif  // MAP_SERIALIZER_H
