#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include <yaml-cpp/yaml.h>
#include "types.h"
#include <string>
#include <vector>


struct TileData {
    int x;
    int y;
    std::string name;
    std::string type;
};

class YamlParser {

private:
    std::string yaml;
    void parseYaml(const std::string& yamlPath);
    TileType stringToTileType(const std::string& typeStr, const std::string& nameStr);

    int mapMinWidth;
    int mapMaxWidth;
    int mapMinHeight;
    int mapMaxHeight;
    std::vector<std::vector<std::string>> tileMatrix;
    std::vector<std::vector<TileType>> typeMatrix;


public:
    explicit YamlParser(const std::string& yamlPath);
    std::vector<std::vector<std::string>> getTileMatrix() const;
    std::vector<std::vector<TileType>> getTypeMatrix() const;
    int getMapWidth() const;
    int getMapHeight() const;
};
#endif // YAML_PARSER_H