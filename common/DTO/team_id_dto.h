#ifndef COMMON_DTO_TEAM_ID_DTO_H
#define COMMON_DTO_TEAM_ID_DTO_H

#include "common/definitions.h"

namespace DTO {
struct TeamIDDTO {
public:
    short_id_t id;

    TeamIDDTO(): id(0) {}
    explicit TeamIDDTO(short_id_t id): id(id) {}
};
};  // namespace DTO

#endif  // COMMON_DTO_TEAM_ID_DTO_H
