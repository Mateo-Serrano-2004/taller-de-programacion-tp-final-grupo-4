#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <cstdint>
#include <iostream>
#include <map>

#include "model/full_player.h"

class MovementSystem {
public:
    MovementSystem() = default;

    void process_movements(std::map<uint8_t, FullPlayer>& players, uint16_t frames_to_process);
};

#endif  // MOVEMENT_SYSTEM_H
