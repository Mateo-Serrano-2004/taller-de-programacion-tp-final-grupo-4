#include "shot_manager.h"
#include <cmath>
#include <limits>
#include <random>

bool does_bullet_hit_player(
    const Physics::Vector2D& origin,
    const Physics::Vector2D& direction,
    float max_range,
    const FullPlayer& player
) {
    Physics::Vector2D pos = player.get_position();
    Physics::Vector2D size = player.get_size();
    float min_x = pos.get_x();
    float min_y = pos.get_y();
    float max_x = pos.get_x() + size.get_x();
    float max_y = pos.get_y() + size.get_y();


    Physics::Vector2D end = origin + direction.normalized() * max_range;

    if (end.get_x() < min_x && origin.get_x() < min_x) return false;
    if (end.get_x() > max_x && origin.get_x() > max_x) return false;
    if (end.get_y() < min_y && origin.get_y() < min_y) return false;
    if (end.get_y() > max_y && origin.get_y() > max_y) return false;

    Physics::Vector2D rect_edges[4][2] = {
        {Physics::Vector2D(min_x, min_y), Physics::Vector2D(max_x, min_y)},
        {Physics::Vector2D(max_x, min_y), Physics::Vector2D(max_x, max_y)},
        {Physics::Vector2D(max_x, max_y), Physics::Vector2D(min_x, max_y)},
        {Physics::Vector2D(min_x, max_y), Physics::Vector2D(min_x, min_y)}
    };

    for (auto& edge : rect_edges) {
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

Physics::Vector2D direction_with_dispersion(float base_angle, float dispersion) {
    static std::default_random_engine generator(std::random_device{}());
    std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

    float random_factor = distribution(generator);
    float actual_angle = base_angle + random_factor * dispersion;

    return Physics::Vector2D(std::cos(actual_angle), std::sin(actual_angle));
}

std::vector<Impact> ShotManager::calculate_shot_impacts(
    const ShotInfo& shot_info,
    const std::map<uint8_t, FullPlayer>& players
) {
    std::vector<Impact> impacts;
    // Imprimir ShotInfo y WeaponShotInfo
    std::cout << "[SHOT INFO]" << std::endl;
    std::cout << "Shooter ID: " << static_cast<int>(shot_info.shooter_id) << std::endl;
    std::cout << "Origin: (" << shot_info.origin.get_x() << ", " << shot_info.origin.get_y() << ")" << std::endl;
    std::cout << "Angle: " << shot_info.angle << std::endl;

    const auto& w = shot_info.weapon_info;
    std::cout << "[WEAPON INFO]" << std::endl;
    std::cout << "Bullets fired: " << static_cast<int>(w.bullets_fired) << std::endl;
    std::cout << "Base damage: " << w.base_damage << std::endl;
    std::cout << "Min damage: " << w.min_damage << std::endl;
    std::cout << "Max range: " << w.max_range << std::endl;
    std::cout << "Precision: " << w.precision << std::endl;
    std::cout << "Dispersion: " << w.dispersion << std::endl;
    std::cout << "Damage mode: " << static_cast<int>(w.damage_mode) << std::endl;
    std::cout << "Falloff factor: " << w.falloff_factor << std::endl;
    std::cout << "Close range threshold: " << w.close_range_threshold << std::endl;
    std::cout << "Close range multiplier: " << w.close_range_multiplier << std::endl;
    const WeaponShotInfo& winfo = shot_info.weapon_info;
    const Physics::Vector2D& origin = shot_info.origin;
    float base_angle = shot_info.angle;

    for (int i = 0; i < winfo.bullets_fired; ++i) {
        Physics::Vector2D direction = direction_with_dispersion(base_angle, winfo.dispersion);

        float closest_dist = std::numeric_limits<float>::max();
        int8_t target_id = 0;
        bool found_target = false;

        for (const auto& [id, player] : players) {
            if (id == shot_info.shooter_id || !player.is_alive()) continue;
            if (!does_bullet_hit_player(origin, direction, winfo.max_range, player)) continue;

            float dist = origin.distance_to(player.get_position());
            if (dist < closest_dist) {
                closest_dist = dist;
                target_id = id;
                found_target = true;
            }
        }

        if (found_target) {
            float damage = calculate_damage(winfo, closest_dist);
            std::cout << "SHOOTER ID :" << static_cast<int>(shot_info.shooter_id) << "TARGET ID: " << static_cast<int>(target_id) << "DAMAGE: " << static_cast<int>(damage) << std::endl;
            impacts.emplace_back(shot_info.shooter_id, target_id, damage);
        }
    }

    return impacts;
}