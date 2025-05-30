#ifndef COMMON_MODEL_PLAYER_H
#define COMMON_MODEL_PLAYER_H

#include <string>

#include "common/DTO/player_dto.h"
#include "common/definitions.h"

#include "vector_2d.h"

namespace Model {
class Player {
protected:
    short_id_t id;
    short_id_t skin_id;
    short_id_t skin_piece;
    angle_t angle;
    std::string name;
    Physics::Vector2D position;

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

public:
    Player(short_id_t id, const std::string& name);

    Player(short_id_t id, short_id_t skin_id, short_id_t skin_piece, angle_t angle,
           const std::string& name, const Physics::Vector2D& position);

    Player(Player&&) = default;
    Player& operator=(Player&&) = default;

    short_id_t get_id() const;
    short_id_t get_skin_id() const;
    short_id_t get_skin_piece() const;
    angle_t get_angle() const;
    std::string get_name() const;
    Physics::Vector2D get_position() const;

    void set_skin_id(short_id_t new_skin_id);
    void set_skin_piece(short_id_t new_skin_piece);
    void set_angle(angle_t new_angle);
    void set_position(Physics::Vector2D new_position);

    DTO::PlayerDTO to_dto() const;

    virtual ~Player() = default;
};
};  // namespace Model

#endif  // COMMON_MODEL_PLAYER_H
