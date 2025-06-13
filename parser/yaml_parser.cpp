#include "yaml_parser.h"
#include <yaml-cpp/yaml.h>
#include <iostream>

YamlParser::YamlParser(const std::string& yamlPath) {
    parseYaml(yamlPath);
}

void YamlParser::parseYaml(const std::string& yamlPath) {
    YAML::Node root = YAML::LoadFile(yamlPath);
    
    mapWidth = root["map"]["width"].as<int>();//PENDING agregarlo al guadado del yaml
    mapHeight = root["map"]["height"].as<int>();

    tileMatrix.resize(mapHeight, std::vector<std::string>(mapWidth, ""));

    for (const auto& tile : root["tiles"]) {
        int x = tile["x"].as<int>();
        int y = tile["y"].as<int>();
        std::string path = tile["path"].as<std::string>();
        std::string type = tile["type"].as<std::string>();

        std::string filename = path.substr(path.find_last_of('/') + 1);

        if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight) {
            tileMatrix[y][x] = filename;
        }

        /*if (isCollidable(type)) {
            collidables.insert({x, y});
        }*/
    }
}

std::vector<std::vector<std::string>> YamlParser::getYamlTiles() {
    return tileMatrix;
}
/*
bool YamlParser::isCollidable(std::string type) {
    return type == "wall" || type == "box" || type == "car";
}


bool isABomb(const std::string type) {
    return (type == "sites");
}*/