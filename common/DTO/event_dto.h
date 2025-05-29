#ifndef COMMON_DTO_EVENT_DTO_H
#define COMMON_DTO_EVENT_DTO_H

#include <cstdint>
#include <vector>

namespace DTO {
struct EventDTO {
public:
    uint8_t size;
    std::vector<char> data;
};
}  // namespace DTO

#endif  // COMMON_DTO_EVENT_DTO_H
