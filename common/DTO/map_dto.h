#ifndef COMMON_DTO_MAP_DTO_H
#define COMMON_DTO_MAP_DTO_H

#include <vector>
#include <string>

#include "common/definitions.h"

using PathMap = std::vector<std::vector<std::string>>;
using PathRow = std::vector<std::string>;

namespace DTO {
struct MapDTO {
public:
    uint8_t count_of_columns;
    uint8_t count_of_rows;
    PathMap map;

    MapDTO() : count_of_columns(0), count_of_rows(0) {}
    MapDTO(const PathMap& map) : map(map), count_of_columns(map.size()), count_of_rows(map[0].size()) {}
};
};

#endif // COMMON_DTO_MAP_DTO_H
