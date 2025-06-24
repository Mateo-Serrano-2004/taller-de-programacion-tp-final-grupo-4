#ifndef SERVER_GAME_LOGIC_SHOT_MANAGER_H
#define SERVER_GAME_LOGIC_SHOT_MANAGER_H

#include <cstdint>
#include <map>
#include <vector>

#include "server/game/model/full_player.h"
#include "server/game/model/impact.h"
#include "server/game/model/shot_info.h"
#include "server/parser/types.h"
#include "server/parser/yaml_parser.h"

class ShotManager {
public:
    static std::vector<Impact> calculate_shot_impacts(const ShotInfo& shot_info,
                                                      const std::map<uint8_t, FullPlayer>& players,
                                                      const MapMatrix& map_matrix);
};

#endif  // SERVER_GAME_LOGIC_SHOT_MANAGER_H
