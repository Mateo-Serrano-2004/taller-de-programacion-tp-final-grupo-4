#ifndef COMMON_DTO_MAP_NAME_LIST_DTO_H
#define COMMON_DTO_MAP_NAME_LIST_DTO_H

#include <string>
#include <vector>

#include "common/definitions.h"

namespace DTO {
struct MapNameListDTO {
public:
    std::vector<std::string> maps_names;

    MapNameListDTO() = default;
    explicit MapNameListDTO(const std::vector<std::string>& maps_names): maps_names(maps_names) {}
};
};  // namespace DTO

#endif  // COMMON_DTO_MAP_NAME_LIST_DTO_H
