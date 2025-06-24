#include "shot_manager.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <random>
#include <utility>

bool does_bullet_hit_player(const Physics::Vector2D& origin, const Physics::Vector2D& end,
                            const FullPlayer& player) {
    Physics::Vector2D pos = player.get_position();
    Physics::Vector2D size = player.get_size();
    float min_x = pos.get_x();
    float min_y = pos.get_y();
    float max_x = pos.get_x() + size.get_x();
    float max_y = pos.get_y() + size.get_y();

    if (end.get_x() < min_x && origin.get_x() < min_x)
        return false;
    if (end.get_x() > max_x && origin.get_x() > max_x)
        return false;
    if (end.get_y() < min_y && origin.get_y() < min_y)
        return false;
    if (end.get_y() > max_y && origin.get_y() > max_y)
        return false;

    Physics::Vector2D rect_edges[4][2] = {
            {Physics::Vector2D(min_x, min_y), Physics::Vector2D(max_x, min_y)},
            {Physics::Vector2D(max_x, min_y), Physics::Vector2D(max_x, max_y)},
            {Physics::Vector2D(max_x, max_y), Physics::Vector2D(min_x, max_y)},
            {Physics::Vector2D(min_x, max_y), Physics::Vector2D(min_x, min_y)}};

    for (auto& edge: rect_edges) {
        if (Physics::Vector2D::segments_intersect(origin, end, edge[0], edge[1])) {
            return true;
        }
    }

    return false;
}

float calculate_damage(const WeaponShotInfo& info, float distance) {
    switch (info.damage_mode) {
        case DamageMode::CONSTANT:
            return info.base_damage;

        case DamageMode::LINEAR_FALLOFF:
            return std::max(info.min_damage, info.base_damage - distance * info.falloff_factor);

        case DamageMode::SHORT_RANGE_BOOST:
            if (distance <= info.close_range_threshold) {
                return info.base_damage * info.close_range_multiplier;
            }
            return std::max(info.min_damage, info.base_damage - distance * info.falloff_factor);
    }

    return info.base_damage;
}

Physics::Vector2D calculate_bullet_endpoint(const Physics::Vector2D& origin,
                                            float base_angle_degrees, float dispersion_degrees,
                                            float max_range, float precision) {
    static std::default_random_engine generator(std::random_device{}());
    std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

    constexpr float DEG_TO_RAD = 3.14159265f / 180.0f;

    float random_factor = distribution(generator);
    float effective_dispersion = (1.0f - precision) * dispersion_degrees;
    float final_angle = base_angle_degrees + random_factor * effective_dispersion;

    float fixed_angle = 90.0f - final_angle;
    float angle_radians = fixed_angle * DEG_TO_RAD;

    float dx = std::cos(angle_radians) * max_range;
    float dy = std::sin(angle_radians) * max_range;

    return Physics::Vector2D(origin.get_x() + dx, origin.get_y() + dy);
}

bool collidable_blocking_bullet(const Physics::Vector2D& origin, const Physics::Vector2D& end,
                                float max_distance, const MapMatrix& map_matrix) {

    if (origin == end)
        return false;

    std::pair<float, float> direction = (end - origin).normalized();
    float step_size = TILE_SIZE / 4.0f;

    float x_step = direction.first * step_size;
    float y_step = direction.second * step_size;

    float x = origin.get_x();
    float y = origin.get_y();

    float dist = 0.0f;

    while (dist < max_distance) {
        Physics::Vector2D current(x, y);
        dist = current.distance_to(origin);

        int tile_x = static_cast<int>(x) / TILE_SIZE;
        int tile_y = static_cast<int>(y) / TILE_SIZE;

        if (tile_y < 0 || tile_y >= static_cast<int>(map_matrix.size()) || tile_x < 0 ||
            tile_x >= static_cast<int>(map_matrix[0].size())) {
            return false;
        }

        if (map_matrix[tile_y][tile_x] == TileType::COLLIDABLE) {
            return true;
        }

        x += x_step;
        y += y_step;
    }

    return false;
}

std::vector<Impact> ShotManager::calculate_shot_impacts(
        const ShotInfo& shot_info, const std::map<uint8_t, FullPlayer>& players,
        const MapMatrix& map_matrix) {
    std::vector<Impact> impacts;

    const WeaponShotInfo& winfo = shot_info.weapon_info;
    const Physics::Vector2D& origin = shot_info.origin;
    float base_angle = shot_info.angle - 2 * (shot_info.angle - 270);

    for (int i = 0; i < winfo.bullets_fired; ++i) {
        Physics::Vector2D end = calculate_bullet_endpoint(origin, base_angle, winfo.dispersion,
                                                          winfo.max_range, winfo.precision);

        float closest_dist = std::numeric_limits<float>::max();
        int8_t target_id = 0;
        bool found_target = false;

        for (const auto& [id, player]: players) {
            if (id == shot_info.shooter_id || !player.is_alive())
                continue;

            if (!does_bullet_hit_player(origin, end, player))
                continue;

            float dist_to_player = origin.distance_to(player.get_position());

            if (dist_to_player < closest_dist) {
                closest_dist = dist_to_player;
                target_id = id;
                found_target = true;
            }
        }

        if (found_target && !collidable_blocking_bullet(origin, end, closest_dist, map_matrix)) {
            float damage = calculate_damage(winfo, closest_dist);
            impacts.emplace_back(shot_info.shooter_id, target_id, damage);
        }
    }

    return impacts;
}
