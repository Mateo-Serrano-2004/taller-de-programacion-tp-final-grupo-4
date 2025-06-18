#ifndef CLIENT_GAME_INTERFACE_TRANSFERED_H
#define CLIENT_GAME_INTERFACE_TRANSFERED_H

#include "common/DTO/event_dto.h"

class Transfered {
public:
    virtual DTO::EventDTO as_dto() = 0;
    virtual ~Transfered() = default;
};

#endif  // CLIENT_GAME_INTERFACE_TRANSFERED_H
