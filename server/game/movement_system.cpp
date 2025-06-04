#include "movement_system.h"

void MovementSystem::process_movements(std::map<uint8_t, Model::MovablePlayer>& players, uint16_t frames_to_process) {

    for (auto& [id, player] : players) {

        if(!player.is_alive()) continue;

        //Esto va chequeando cada posición y moviendo de a uno.
        //Podría tener un next = pos + dir * frames_to_process asi calculo el punto final directamente
        // y solo reviso si en la linea esa debio chocarse con algo y lo dejo donde chocó (medio lo mismo)
        for(int i = 0; i < static_cast<int>(frames_to_process); i++){
            Physics::Vector2D dir = player.get_direction();
            Physics::Vector2D pos = player.get_position();
            Physics::Vector2D next = pos + dir;

            // Algo como un mapa muy basico donde en (10,0) y en (0,10) hay un collidable.
            int x = static_cast<int>(next.get_x());
            int y = static_cast<int>(next.get_y());

            if (x < 0 || x >= 30 || y < 0 || y >= 30 || (x == 10 && y == 0) || (x == 0 && y == 10)) {
                player.stop_horizontal_movement();
                player.stop_vertical_movement();
                i = frames_to_process; // ya chocó ya deengo el for
            } else {
                player.set_position(next);
            }
        }
    }
}
