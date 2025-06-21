#include "movement_system.h"

constexpr int TILE_SIZE = 32;

MovementSystem::MovementSystem(const std::vector<std::vector<TileType>>& type_matrix) {
    for (int y = 0; y < static_cast<int>(type_matrix.size()); ++y) {
        for (int x = 0; x < static_cast<int>(type_matrix[y].size()); ++x) {
            if (type_matrix[y][x] == COLLIDABLE) {
                BoundingBox box;
                box.x = x * TILE_SIZE;
                box.y = y * TILE_SIZE;
                box.w = TILE_SIZE;
                box.h = TILE_SIZE;
                collidable_boxes.push_back(box);
            }
        }
    }
}

bool MovementSystem::is_colliding_with_map(const Physics::Vector2D& position,
                                           const Physics::Vector2D& size) const {
    int left = static_cast<int>(position.get_x());
    int top = static_cast<int>(position.get_y());
    int right = left + static_cast<int>(size.get_x());
    int bottom = top + static_cast<int>(size.get_y());

    for (const BoundingBox& box : collidable_boxes) {
        bool overlap_x = !(right <= box.x || left >= box.x + box.w);
        bool overlap_y = !(bottom <= box.y || top >= box.y + box.h);

        if (overlap_x && overlap_y)
            return true;
    }

    return false;
}

bool MovementSystem::is_colliding_with_other_players(const Physics::Vector2D& pos,
                                                     const Physics::Vector2D& size,
                                                     uint8_t current_id,
                                                     const std::map<uint8_t, FullPlayer>& players) const {
    int left = static_cast<int>(pos.get_x());
    int top = static_cast<int>(pos.get_y());
    int right = left + static_cast<int>(size.get_x());
    int bottom = top + static_cast<int>(size.get_y());

    for (const auto& [id, other] : players) {
        if (id == current_id) continue;
        if (!other.is_alive()) continue;

        Physics::Vector2D other_pos = other.get_position();
        Physics::Vector2D other_size = other.get_size();

        int o_left = static_cast<int>(other_pos.get_x());
        int o_top = static_cast<int>(other_pos.get_y());
        int o_right = o_left + static_cast<int>(other_size.get_x());
        int o_bottom = o_top + static_cast<int>(other_size.get_y());

        bool overlap_x = !(right <= o_left || left >= o_right);
        bool overlap_y = !(bottom <= o_top || top >= o_bottom);

        if (overlap_x && overlap_y) {
            return true;
        }
    }

    return false;
}

void MovementSystem::process_movements(std::map<uint8_t, FullPlayer>& players, uint16_t frames_to_process) {
    for (auto& [id, player] : players) {
        if (!player.is_alive()) continue;

        Physics::Vector2D dir = player.get_direction();
        if (dir.get_x() == 0 && dir.get_y() == 0) continue;

        Physics::Vector2D pos = player.get_position();
        Physics::Vector2D size = player.get_size();

        for (int i = 0; i < frames_to_process; ++i) {
            Physics::Vector2D next = pos + dir;

            if (/*is_colliding_with_map(next, size) ||*/
                is_colliding_with_other_players(next, size, id, players)) {
                if (dir.get_x() != 0) player.stop_horizontal_movement();
                if (dir.get_y() != 0) player.stop_vertical_movement();
                break;
            }

            pos = next;
        }

        player.set_position(pos);
    }
}


/*void MovementSystem::process_movements(std::map<uint8_t, FullPlayer>& players,
                                       uint16_t frames_to_process) {

    for (auto& [id, player]: players) {

        if (!player.is_alive())
            continue;

        // Esto va chequeando cada posición y moviendo de a uno.
        // Podría tener un next = pos + dir * frames_to_process asi calculo el punto final
        // directamente
        //  y solo reviso si en la linea esa debio chocarse con algo y lo dejo donde chocó (medio lo
        //  mismo)
        for (int i = 0; i < static_cast<int>(frames_to_process); i++) {
            Physics::Vector2D dir = player.get_direction();
            Physics::Vector2D pos = player.get_position();
            Physics::Vector2D next = pos + dir;

            int x = static_cast<int>(next.get_x());
            int y = static_cast<int>(next.get_y());

            if (x < 0 || y < 0) {
                player.stop_horizontal_movement();
                player.stop_vertical_movement();
                i = frames_to_process;  // ya chocó ya deengo el for
            } else {
                player.set_position(next);
            }
        }
    }
}*/
