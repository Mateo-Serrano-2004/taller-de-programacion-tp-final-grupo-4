#include "movement_system.h"

#include "common/definitions.h"

MovementSystem::MovementSystem(const MapMatrix& map_matrix): map_matrix(map_matrix) {}

bool MovementSystem::is_colliding_with_map(const Physics::Vector2D& position,
                                           const Physics::Vector2D& size) const {
    int left = static_cast<int>(position.get_x());
    int top = static_cast<int>(position.get_y());
    int right = left + static_cast<int>(size.get_x());
    int bottom = top + static_cast<int>(size.get_y());

    int tile_left = left / TILE_SIZE;
    int tile_top = top / TILE_SIZE;
    int tile_right = right / TILE_SIZE;
    int tile_bottom = bottom / TILE_SIZE;

    int max_rows = static_cast<int>(map_matrix.size());
    int max_cols = static_cast<int>(map_matrix[0].size());

    if (tile_top < 0 || tile_top >= max_rows || tile_left < 0 || tile_left >= max_cols ||
        tile_bottom < 0 || tile_bottom >= max_rows || tile_right < 0 || tile_right >= max_cols) {
        return true;
    }

    if (map_matrix[tile_top][tile_left] == TileType::COLLIDABLE)
        return true;
    if (map_matrix[tile_top][tile_right] == TileType::COLLIDABLE)
        return true;
    if (map_matrix[tile_bottom][tile_left] == TileType::COLLIDABLE)
        return true;
    if (map_matrix[tile_bottom][tile_right] == TileType::COLLIDABLE)
        return true;

    return false;
}

bool MovementSystem::is_colliding_with_other_players(
        const Physics::Vector2D& pos, const Physics::Vector2D& size, uint8_t current_id,
        const std::map<uint8_t, FullPlayer>& players) const {
    int left = static_cast<int>(pos.get_x());
    int top = static_cast<int>(pos.get_y());
    int right = left + static_cast<int>(size.get_x());
    int bottom = top + static_cast<int>(size.get_y());

    for (const auto& [id, other]: players) {
        if (id == current_id)
            continue;
        if (!other.is_alive())
            continue;

        Physics::Vector2D other_pos = other.get_position();
        Physics::Vector2D other_size = other.get_size();

        int o_left = static_cast<int>(other_pos.get_x());
        int o_top = static_cast<int>(other_pos.get_y());
        int o_right = o_left + static_cast<int>(other_size.get_x());
        int o_bottom = o_top + static_cast<int>(other_size.get_y());

        bool overlap_x = !(right <= o_left || left >= o_right);
        bool overlap_y = !(bottom <= o_top || top >= o_bottom);

        if (overlap_x && overlap_y)
            return true;
    }

    return false;
}

void MovementSystem::try_pick_up_weapon(std::map<uint8_t, FullPlayer>& players, uint8_t player_id,
                                        Round& round) {
    auto player_it = players.find(player_id);
    if (player_it == players.end())
        return;

    FullPlayer& player = player_it->second;
    if (!player.is_alive())
        return;

    Physics::Vector2D pos = player.get_position();
    Physics::Vector2D size = player.get_size();

    int left = static_cast<int>(pos.get_x());
    int top = static_cast<int>(pos.get_y());
    int right = left + static_cast<int>(size.get_x());
    int bottom = top + static_cast<int>(size.get_y());

    auto& drops = round.get_dropped_weapons();

    for (auto it = drops.begin(); it != drops.end(); ++it) {
        const auto& drop = *it;

        const Physics::Vector2D& drop_pos = drop.get_position();
        int drop_left = static_cast<int>(drop_pos.get_x());
        int drop_top = static_cast<int>(drop_pos.get_y());
        int drop_right = drop_left + TILE_SIZE;
        int drop_bottom = drop_top + TILE_SIZE;

        bool overlap_x = !(right <= drop_left || left >= drop_right);
        bool overlap_y = !(bottom <= drop_top || top >= drop_bottom);

        if (overlap_x && overlap_y) {
            Shared<FullWeapon> weapon = drop.get_weapon();
            if (!weapon)
                continue;

            Model::SlotID slot = weapon->get_slot_id();

            bool can_pick_it = false;
            switch (slot) {
                case Model::SlotID::PRIMARY_WEAPON:
                    can_pick_it = !player.has_primary_weapon();
                    break;
                case Model::SlotID::SECONDARY_WEAPON:
                    can_pick_it = !player.has_secondary_weapon();
                    break;
                case Model::SlotID::BOMB_SLOT:
                    can_pick_it =
                            (player.get_team() == Model::TeamID::TT && !player.get_has_bomb());
                    break;
                default:
                    break;
            }

            if (can_pick_it) {
                player.equip_new_weapon_and_drop_previous(weapon);
                drops.erase(it);
                break;
            }
        }
    }
}

void MovementSystem::process_movements(std::map<uint8_t, FullPlayer>& players, Round& round,
                                       uint16_t frames_to_process,
                                       bool players_collisions_enabled) {
    if (round.is_buying())
        return;
    for (auto& [id, player]: players) {
        if (!player.is_alive())
            continue;

        Physics::Vector2D dir = player.get_direction();
        if (dir.get_x() == 0 && dir.get_y() == 0)
            continue;

        Physics::Vector2D pos = player.get_position();
        Physics::Vector2D size = player.get_size();

        for (int i = 0; i < frames_to_process; ++i) {
            Physics::Vector2D next = pos + dir;

            if (is_colliding_with_map(next, size) ||
                (players_collisions_enabled &&
                 is_colliding_with_other_players(next, size, id, players))) {
                if (dir.get_x() != 0)
                    player.stop_horizontal_movement();
                if (dir.get_y() != 0)
                    player.stop_vertical_movement();
                break;
            }

            pos = next;

            try_pick_up_weapon(players, id, round);
        }

        player.set_position(pos);
    }
}
