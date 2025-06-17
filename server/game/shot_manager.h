#ifndef SERVER_GAME_LOGIC_SHOT_MANAGER_H
#define SERVER_GAME_LOGIC_SHOT_MANAGER_H

#include <vector>
#include <map>
#include <cstdint>

#include "server/game/model/shot_info.h"
#include "server/game/model/impact.h"
#include "server/game/model/full_player.h"

class ShotManager {
public:
    static std::vector<Impact> calculate_shot_impacts(const ShotInfo& shot_info, const std::map<uint8_t, FullPlayer>& players);
};

#endif // SERVER_GAME_LOGIC_SHOT_MANAGER_H