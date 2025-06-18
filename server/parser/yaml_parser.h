#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include <map>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "types.h"

struct TileData {
    int x;
    int y;
    std::string name;
    std::string type;
};

struct GameConfig {
    std::string title;
    int rounds;
    int roundsToWin;
    int roundsPerSide;
    int buyTime;
    int warmupTime;
    int roundTime;
    int roundWonMoney;
    int roundLostMoney;
    int bombExplotionTime;
    int bombExplotionRadius;
    int bombExplotionDamage;
    int bombPlantTime;
    int bombDefuseTime;
    int bombPlantMoney;
    int bombDefuseMoney;
};

struct PlayerConfig {
    int health;
    int initialMoney;
    float movementSpeed;
};

struct WeaponConfig {
    int damagePerBullet;
    int maxAmmo;
    int initialAmmo;
    float precision;
    int cost;
    int range;
    int bulletsPerShot;
    float fireRate;
    int bountyMoney;
    float reloadTime;
};

struct FovConfig {
    int angle;
    int ratio;
};

struct DisplayConfig {
    int widht;
    int height;
};

struct ConfigData {
    GameConfig game;
    PlayerConfig player;
    std::map<std::string, WeaponConfig> weapons;
    FovConfig fov;
    DisplayConfig display;
};

class YamlParser {

private:
    ConfigData gameConfig;
    std::vector<std::vector<std::string>> tileMatrix;
    std::vector<std::vector<TileType>> typeMatrix;

    void parseGameConfigYaml(const std::string& yamlGameConfigPath);
    TileType stringToTileType(const std::string& typeStr, const std::string& nameStr);

public:
    explicit YamlParser(const std::string& yamlGameConfigPath);
    void parseMapYaml(const std::string& yamlMapPath);
    std::vector<std::vector<std::string>> getTileMatrix() const;
    std::vector<std::vector<TileType>> getTypeMatrix() const;
    const ConfigData& getConfigData() const;
};
#endif  // YAML_PARSER_H
