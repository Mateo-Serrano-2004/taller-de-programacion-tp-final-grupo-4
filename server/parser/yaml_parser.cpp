#include "yaml_parser.h"
#include <yaml-cpp/yaml.h>
#include <iostream>

YamlParser::YamlParser(const std::string& yamlMapPath, const std::string& yamlGameConfigPath) {
    parseMapYaml(yamlMapPath);
    parseGameConfigYaml(yamlGameConfigPath);
}

void YamlParser::parseMapYaml(const std::string& yamlPath) {
    YAML::Node root = YAML::LoadFile(yamlPath);
    
    mapMinWidth = root["map"]["minWidht"].as<int>();
    mapMaxWidth = root["map"]["maxWidht"].as<int>();

    mapMinHeight = root["map"]["minHeight"].as<int>();
    mapMaxHeight = root["map"]["maxHeight"].as<int>();

    int mapWidth = mapMaxWidth - mapMinWidth + 1;
    int mapHeight = mapMaxHeight - mapMinHeight + 1;

    tileMatrix.resize(mapHeight, std::vector<std::string>(mapWidth, ""));
    typeMatrix.resize(mapHeight, std::vector<TileType>(mapWidth, COLLIDABLE));

    for (const auto& tile : root["tiles"]) {
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

void YamlParser::parseGameConfigYaml(const std::string& yamlPath) {
    YAML::Node config = YAML::LoadFile(yamlGameConfigPath);

    // Game
    const auto& game = config["game"];
    gameConfig.game.title = game["title"].as<std::string>();
    gameConfig.game.rounds = game["rounds"].as<int>();
    gameConfig.game.prepareTime = game["prepare_time"].as<int>();
    gameConfig.game.killPoints = game["kill_points"].as<int>();
    gameConfig.game.roundWonPoints = game["round_won_points"].as<int>();
    gameConfig.game.roundLostPoints = game["round_lost_points"].as<int>();
    gameConfig.game.bombExplotionTime = game["bomb_explotion_time"].as<int>();

    // Players
    //Terrorists
    const auto& players = config["player"];
    const auto& terrorist = players["terrorist"];
    gameConfig.terrorist.health = terrorist["health"].as<int>();
    gameConfig.terrorist.moneyPoints = terrorist["money_points"].as<int>();
    gameConfig.terrorist.maxWeapons = terrorist["max_weapons"].as<int>();
    gameConfig.terrorist.movementSpeed = terrorist["movement_speed"].as<float>();
    gameConfig.terrorist.killsCounter = terrorist["kills_counter"].as<int>();
    //Anti-Terrorists
    const auto& antiTerrorist = players["anti-terrorist"];
    gameConfig.antiTerrorist.health = antiTerrorist["health"].as<int>();
    gameConfig.antiTerrorist.moneyPoints = antiTerrorist["money_points"].as<int>();
    gameConfig.antiTerrorist.maxWeapons = antiTerrorist["max_weapons"].as<int>();
    gameConfig.antiTerrorist.movementSpeed = antiTerrorist["movement_speed"].as<float>();
    gameConfig.antiTerrorist.killsCounter = antiTerrorist["kills_counter"].as<int>();

    // Weapons
    const auto& weapons = config["weapons"];
    for (const auto& weapon : weapons) {
        std::string name = weapon.first.as<std::string>();
        const auto& w = weapon.second;

        WeaponConfig wc;
        wc.minDamage = w["min_damage"].as<int>();
        wc.maxDamage = w["max_damage"].as<int>();
        wc.precision = w["precision"].as<float>();
        wc.cost = w["cost"].as<int>();
        wc.range = w["range"].as<int>();
        wc.bulletsPerShot = w["bullets_per_shot"].as<int>();
        wc.fireRate = w["fire_rate"] ? w["fire_rate"].as<float>() : 0.0f;

        gameConfig.weapons[name] = wc;
    }
}

std::vector<std::vector<std::string>> YamlParser::getTileMatrix() const{
    return tileMatrix;
}

std::vector<std::vector<TileType>> YamlParser::getTypeMatrix() const{
    return typeMatrix;
}

TileType YamlParser::stringToTileType(const std::string& typeStr, const std::string& nameStr) {
    if (typeStr == "Backgrounds") return NOT_COLLIDABLE;
    if (typeStr == "Boxes" || typeStr == "Cars" || typeStr == "Walls") return COLLIDABLE;
    if (typeStr == "Sites") return BOMB_SITE;
    if (nameStr.find("ct") != std::string::npos) return CT_SPAWN;
    if (nameStr.find("tt") != std::string::npos) return TT_SPAWN;
    return NOT_COLLIDABLE;  
}

const ConfigData& YamlParser::getConfigData() const {
    return gameConfig;
}