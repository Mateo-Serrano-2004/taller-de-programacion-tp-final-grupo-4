#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include <map>
#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "types.h"

class YamlParser;

struct TileData {
    int x;
    int y;
    std::string name;
    std::string type;
};

struct GameConfig {
    std::string title;
    int rounds;
    int roundsPerSide;
    int buyTime;
    int warmupTime;
    int postRoundTime;
    int roundTime;
    int roundWonMoney;
    int roundLostMoney;
    int bombExplotionTime;
    int bombPlantTime;
    int bombDefuseTime;
    int killMoney;
    int costPrimaryAmmo;
    int costSecondaryAmmo;
};

struct PlayerConfig {
    int health;
    int initialMoney;
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
    float dispersion;
    float reloadTime;
};

struct FovConfig {
    int angle;
    int ratio;
    int opacity;
};

struct DisplayConfig {
    int width;
    int height;
};

struct ConfigData {
    friend class YamlParser;

public:
    GameConfig game{};
    PlayerConfig player{};
    std::map<std::string, WeaponConfig> weapons;
    FovConfig fov{};
    DisplayConfig display{};

private:
    ConfigData() = default;
    ConfigData(const ConfigData&) = delete;
    ConfigData& operator=(const ConfigData&) = delete;
};

class YamlParser {
private:
    static ConfigData gameConfig;
    std::vector<std::vector<std::string>> tileMatrix;
    std::vector<std::vector<TileType>> typeMatrix;

    void parseGameConfigYaml(const std::string& yamlGameConfigPath);
    TileType stringToTileType(const std::string& typeStr, const std::string& nameStr);

public:
    explicit YamlParser(const std::string& yamlGameConfigPath);
    void parseMapYaml(const std::string& yamlMapPath);
    std::vector<std::vector<std::string>> getTileMatrix() const;
    std::vector<std::vector<TileType>> getTypeMatrix() const;
    static const ConfigData& getConfigData();
};
#endif  // YAML_PARSER_H
