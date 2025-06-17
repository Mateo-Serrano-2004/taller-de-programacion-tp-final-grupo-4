#ifndef COMMON_DTO_PLAYER_ID_DTO_H
#define COMMON_DTO_PLAYER_ID_DTO_H

#include "common/definitions.h"

namespace DTO {
struct PlayerIDDTO {
public:
    short_id_t id;

    PlayerIDDTO(short_id_t id) : id(id) {}
};
};

#endif // COMMON_DTO_PLAYER_ID_DTO_H
