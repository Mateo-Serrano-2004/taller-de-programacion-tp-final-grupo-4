#ifndef MAP_SERIALIZER_H
#define MAP_SERIALIZER_H

#include <QString>
#include <QGraphicsScene>

class MapSerializer {
public:
    static void saveToYaml(QGraphicsScene* scene, const QString& filePath);
};

#endif // MAP_SERIALIZER_H