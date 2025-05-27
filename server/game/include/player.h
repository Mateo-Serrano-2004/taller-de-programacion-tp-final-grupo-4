#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "../../../common/dto/player_dto.h"
#include "vector2d.h"
#include "enums.h"

class Player {
private:
    uint8_t id;
    std::string username;
    Vector2D position;
    Vector2D direction;
    int angle;

    Team team;
    int health;
    int money;
    
    bool is_alive;
    bool has_bomb;


public:
    Player(uint8_t id, const std::string& username, Team team, int money);

    void set_direction(const Vector2D& dir);
    void update_position();
    void take_damage(int damage);
    bool alive() const;

    PlayerDTO to_dto() const;
};

#endif  // PLAYER_H