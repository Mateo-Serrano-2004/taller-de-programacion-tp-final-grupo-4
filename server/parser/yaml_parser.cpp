#include "yaml_parser.h"

#include <yaml-cpp/yaml.h>

ConfigData YamlParser::gameConfig;

YamlParser::YamlParser(const std::string& yamlGameConfigPath) {
    parseGameConfigYaml(yamlGameConfigPath);
}

void YamlParser::parseMapYaml(const std::string& yamlPath) {
    YAML::Node root = YAML::LoadFile(yamlPath);

    int mapMinWidth = root["map"]["minWidth"].as<int>();
    int mapMaxWidth = root["map"]["maxWidth"].as<int>();

    int mapMinHeight = root["map"]["minHeight"].as<int>();
    int mapMaxHeight = root["map"]["maxHeight"].as<int>();

    int mapWidth = mapMaxWidth - mapMinWidth + 1;
    int mapHeight = mapMaxHeight - mapMinHeight + 1;

    tileMatrix.clear();
    typeMatrix.clear();

    tileMatrix.resize(mapHeight, std::vector<std::string>(mapWidth, ""));
    typeMatrix.resize(mapHeight, std::vector<TileType>(mapWidth, COLLIDABLE));

    for (const auto& tile: root["tiles"]) {
        int initialX = tile["x"].as<int>();
        int initialY = tile["y"].as<int>();
        std::string name = tile["name"].as<std::string>();
        std::string type = tile["type"].as<std::string>();

        int resizedX = initialX - mapMinWidth;
        int resizedY = initialY - mapMinHeight;

        if (resizedX >= 0 && resizedX < mapWidth && resizedY >= 0 && resizedY < mapHeight) {
            tileMatrix[resizedY][resizedX] = type + "/" + name;
            typeMatrix[resizedY][resizedX] = stringToTileType(type, name);
        }
    }
}

void YamlParser::parseGameConfigYaml(const std::string& yamlGameConfigPath) {
    YAML::Node config = YAML::LoadFile(yamlGameConfigPath);

    const auto& game = config["game"];
    gameConfig.game.rounds = game["rounds"].as<int>();
    gameConfig.game.roundsPerSide = game["rounds_per_side"].as<int>();
    gameConfig.game.buyTime = game["buy_time"].as<int>();
    gameConfig.game.warmupTime = game["warmup_time"].as<int>();
    gameConfig.game.postRoundTime = game["post_round_time"].as<int>();
    gameConfig.game.roundTime = game["round_time"].as<int>();
    gameConfig.game.roundWonMoney = game["round_won_money"].as<int>();
    gameConfig.game.roundLostMoney = game["round_lost_money"].as<int>();
    gameConfig.game.bombExplotionTime = game["bomb_explotion_time"].as<int>();
    gameConfig.game.bombPlantTime = game["bomb_plant_time"].as<int>();
    gameConfig.game.bombDefuseTime = game["bomb_defuse_time"].as<int>();
    gameConfig.game.killMoney = game["kill_money"].as<int>();
    gameConfig.game.costPrimaryAmmo = game["cost_primary_ammo"].as<int>();
    gameConfig.game.costSecondaryAmmo = game["cost_secondary_ammo"].as<int>();

    const auto& player = config["player"];
    gameConfig.player.health = player["health"].as<int>();
    gameConfig.player.initialMoney = player["initial_money"].as<int>();

    const auto& weapons = config["weapons"];
    for (const auto& weapon: weapons) {
        std::string name = weapon.first.as<std::string>();
        const auto& w = weapon.second;

        WeaponConfig wc;
        wc.damagePerBullet = w["damage_per_bullet"].as<int>();
        wc.maxAmmo = w["max_ammo"].as<int>();
        wc.initialAmmo = w["initial_ammo"].as<int>();
        wc.precision = w["precision"].as<float>();
        wc.cost = w["cost"].as<int>();
        wc.range = w["range"].as<int>();
        wc.bulletsPerShot = w["bullets_per_shot"].as<int>();
        wc.fireRate = w["fire_rate"] ? w["fire_rate"].as<float>() : 0.0f;
        wc.dispersion = w["dispersion"].as<float>();
        wc.reloadTime = w["reload_time"].as<float>();

        gameConfig.weapons[name] = wc;
    }

    gameConfig.fov.angle = config["fov"]["angle"].as<int>();
    gameConfig.fov.ratio = config["fov"]["ratio"].as<int>();
    gameConfig.fov.opacity = config["fov"]["opacity"].as<int>();

    gameConfig.display.width = config["display"]["width"].as<int>();
    gameConfig.display.height = config["display"]["height"].as<int>();
}

std::vector<std::vector<std::string>> YamlParser::getTileMatrix() const { return tileMatrix; }

std::vector<std::vector<TileType>> YamlParser::getTypeMatrix() const { return typeMatrix; }

TileType YamlParser::stringToTileType(const std::string& typeStr, const std::string& nameStr) {
    if (typeStr == "Backgrounds")
        return NOT_COLLIDABLE;
    if (typeStr == "Boxes" || typeStr == "Cars" || typeStr == "Walls")
        return COLLIDABLE;
    if (typeStr == "Sites")
        return BOMB_SITE;
    if (nameStr.find("ct") != std::string::npos)
        return CT_SPAWN;
    if (nameStr.find("tt") != std::string::npos)
        return TT_SPAWN;
    return NOT_COLLIDABLE;
}

const ConfigData& YamlParser::getConfigData() { return gameConfig; }
