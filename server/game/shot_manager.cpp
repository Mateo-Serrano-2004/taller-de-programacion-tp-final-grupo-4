#include "shot_manager.h"
#include <vector>

std::vector<Impact> ShotManager::calculate_shot_impacts(
    const ShotInfo& shot_info,
    const std::map<uint8_t, FullPlayer>& players
) {
    std::vector<Impact> impacts;

    for (const auto& [id, player] : players) {
        // TODO: Prevent friendly fire
        if (id == shot_info.shooter_id || !player.is_alive()) continue;

        // Impacto dummy: 50 de daño fijo
        impacts.emplace_back(shot_info.shooter_id, id, 50);
        break;  // Solo un impacto, al primero que se encuentre
    }

    return impacts;
}
