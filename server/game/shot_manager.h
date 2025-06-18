#ifndef SERVER_GAME_LOGIC_SHOT_MANAGER_H
#define SERVER_GAME_LOGIC_SHOT_MANAGER_H

#include <cstdint>
#include <map>
#include <vector>

#include "server/game/model/full_player.h"
#include "server/game/model/impact.h"
#include "server/game/model/shot_info.h"

class ShotManager {
public:
    static std::vector<Impact> calculate_shot_impacts(const ShotInfo& shot_info,
                                                      const std::map<uint8_t, FullPlayer>& players);
};

#endif  // SERVER_GAME_LOGIC_SHOT_MANAGER_H
