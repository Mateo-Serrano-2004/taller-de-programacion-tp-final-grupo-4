#ifndef COMMON_DTO_MATCH_DTO_H
#define COMMON_DTO_MATCH_DTO_H

#include "common/model/player.h"

#include <vector>

namespace DTO {
    struct MatchDTO {
        std::vector<Player> players;
    }
};

#endif // COMMON_DTO_MATCH_DTO_H
