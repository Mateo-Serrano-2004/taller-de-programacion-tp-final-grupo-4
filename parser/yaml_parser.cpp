#include "yaml_parser.h"
#include <yaml-cpp/yaml.h>
#include <iostream>

YamlParser::YamlParser(const std::string& yamlPath) {
    parseYaml(yamlPath);
}

void YamlParser::parseYaml(const std::string& yamlPath) {
    YAML::Node root = YAML::LoadFile(yamlPath);
    
    mapMinWidth = root["map"]["minWidht"].as<int>();
    mapMaxWidth = root["map"]["maxWidht"].as<int>();

    mapMinHeight = root["map"]["minHeight"].as<int>();
    mapMaxHeight = root["map"]["maxHeight"].as<int>();

    int mapWidth = mapMaxWidth - mapMinWidth + 1;
    int mapHeight = mapMaxHeight - mapMinHeight + 1;

    tileMatrix.resize(mapHeight, std::vector<std::string>(mapWidth, ""));
    typeMatrix.resize(mapHeight, std::vector<TileType>(mapWidth, UNKNOWN));

    for (const auto& tile : root["tiles"]) {
        int initialX = tile["x"].as<int>();
        int initialY = tile["y"].as<int>();
        std::string path = tile["path"].as<std::string>();
        std::string type = tile["type"].as<std::string>();

        int resizedX = initialX - mapMinWidth;
        int resizedY = initialY - mapMinHeight;

        //std::string filename = path.substr(path.find_last_of('/') + 1);

        if (resizedX >= 0 && resizedX < mapWidth && resizedY >= 0 && resizedY < mapHeight) {
            tileMatrix[resizedY][resizedX] = path;
            typeMatrix[resizedY][resizedX] = stringToTileType(type);
        }

    }
}

std::vector<std::vector<std::string>> YamlParser::getTileMatrix() const{
    return tileMatrix;
}


std::vector<std::vector<TileType>> YamlParser::getTypeMatrix() const{
    return typeMatrix;
}

TileType YamlParser::stringToTileType(const std::string& typeStr) {
    if (typeStr == "background") return BACKGROUND;
    if (typeStr == "wall") return WALL;
    if (typeStr == "box" || typeStr == "car") return WALL;
    if (typeStr == "site" || typeStr == "bomb") return BOMB_SITE;
    if (typeStr == "spawn") return SPAWN;
    return UNKNOWN;
}