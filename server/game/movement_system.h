#ifndef MOVEMENT_SYSTEM_H
#define MOVEMENT_SYSTEM_H

#include <map>
#include <cstdint>
#include "model/movable_player.h"
#include <iostream>

class MovementSystem {
public:
    MovementSystem() = default;

    void process_movements(std::map<uint8_t, MovablePlayer>& players, uint16_t frames_to_process);
};

#endif  // MOVEMENT_SYSTEM_H
