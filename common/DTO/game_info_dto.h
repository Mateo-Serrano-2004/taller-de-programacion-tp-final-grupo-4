#ifndef GAME_INFO_DTO_H
#define GAME_INFO_DTO_H

#include <cstdint>
#include <string>

struct GameInfoDTO {
    uint8_t id;
    std::string name;
    uint8_t current_players;
    uint8_t max_players = 10;
    std::string map_name;

    GameInfoDTO(): id(0), name(""), current_players(0), map_name("") {}
    GameInfoDTO(uint8_t id, const std::string& name, uint8_t current_players,
                const std::string& map_name):
            id(id), name(name), current_players(current_players), map_name(map_name) {}
};

#endif  // GAME_INFO_DTO_H
