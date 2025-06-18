#ifndef COMMON_DTO_GAME_INFO_DTO_H
#define COMMON_DTO_GAME_INFO_DTO_H

#include <cstdint>
#include <string>

namespace DTO {
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
}  // namespace DTO

#endif  // COMMON_DTO_GAME_INFO_DTO_H
