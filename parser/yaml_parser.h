#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include <unordered_set>
#include <string>
#include <vector>
#include <tuple>

struct TileData {
    int x;
    int y;
    std::string type;
    std::string path;
};

class YamlParser {

private:
    std::string yaml;
    void parseYaml(const std::string& yamlPath);

    bool isCollidable(std::string type);
    bool isABomb(std::string type);

    int mapWidth = 0;
    int mapHeight = 0;
    std::vector<std::vector<std::string>> tileMatrix;
    std::vector<std::pair<int, int>, std::string> collidables;


public:
    explicit YamlParser(const std::string& yamlPath);
    std::vector<std::vector<std::string>> getYamlTiles();
    //std::vector<std::pair<int, int>> getCollidables() const;
    int getMapWidth() const;
    int getMapHeight() const;
};
#endif // YAML_PARSER_H