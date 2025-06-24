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
    int rounds;//LISTO
    int roundsToWin;//-------------------------> NO ES NECESARIO
    int roundsPerSide;//LISTO
    int buyTime;//LISTO
    int warmupTime;//LISTO
    int roundTime;//LISTO
    int roundWonMoney;//LISTO
    int roundLostMoney;//LISTO
    int bombExplotionTime;//LISTO
    int bombExplotionRadius;//CONSTANTE DEFINITIONS
    int bombExplotionDamage;//NO SE IMPLEMENTA
    int bombPlantTime;//*********BOMBA
    int bombDefuseTime;//LISTO
    int bombPlantMoney;//NO
    int bombDefuseMoney;//NO
    //no hay post roudn time
    //no hay premio por muerte
};

struct PlayerConfig {
    int health;//LISTO
    int initialMoney;//LISTO
    float movementSpeed;//NO
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
