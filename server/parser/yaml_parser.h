#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include <yaml-cpp/yaml.h>
#include "types.h"
#include <string>
#include <vector>
#include <map>

struct TileData {
    int x;
    int y;
    std::string name;
    std::string type;
};

struct GameConfig {
    std::string title;
    int rounds;
    int prepareTime;
    int killPoints;
    int roundWonPoints;
    int roundLostPoints;
    int bombExplotionTime; //time will always be measeured in seconds
};

struct PlayerConfig {
    int health;
    int moneyPoints;
    int maxWeapons;
    float movementSpeed;
    int killsCounter;
};

struct WeaponConfig {
    int minDamage;
    int maxDamage;
    float precision;
    int cost;
    int range;
    int bulletsPerShot;
    float fireRate;
};

struct ConfigData {
    GameConfig game;
    PlayerConfig terrorist;
    PlayerConfig antiTerrorist;
    std::map<std::string, WeaponConfig> weapons;
};

class YamlParser {

private:
    std::string yamlMapPath, yamlGameConfigPath;
    ConfigData gameConfig;

    void parseMapYaml(const std::string& yamlMapPath);
    void parseGameConfigYaml(const std::string& yamlGameConfigPath);

    TileType stringToTileType(const std::string& typeStr, const std::string& nameStr);

    int mapMinWidth, mapMaxWidth, mapMinHeight, mapMaxHeight;

    std::vector<std::vector<std::string>> tileMatrix;
    std::vector<std::vector<TileType>> typeMatrix;


public:
    YamlParser(const std::string& yamlMapPath, const std::string& yamlGameConfigPath);
    std::vector<std::vector<std::string>> getTileMatrix() const;
    std::vector<std::vector<TileType>> getTypeMatrix() const;
    const ConfigData& getConfigData() const;
    int getMapWidth() const;
    int getMapHeight() const;
};
#endif // YAML_PARSER_H