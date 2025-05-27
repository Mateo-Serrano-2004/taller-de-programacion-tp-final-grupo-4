#ifndef CLIENT_GAME_MODEL_PLAYER_H
#define CLIENT_GAME_MODEL_PLAYER_H

#include <cstdint>

namespace Model {
    class Player {
    private:
        const int16_t default_angle;
        uint16_t id;
        int32_t x;
        int32_t y;
        int16_t angle;
        uint8_t skin_id;
        uint8_t skin_piece;

        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;

    public:
        Player(uint16_t id, int32_t x, int32_t y, int16_t angle, uint8_t skin_id);

        Player(Player&&) = default;
        Player& operator=(Player&&) = default;

        uint16_t get_id() const;
        int32_t get_x() const;
        int32_t get_y() const;
        int16_t get_angle() const;
        uint8_t get_skin_id() const;
        uint8_t get_skin_piece() const;

        void set_x(int32_t new_x);
        void set_y(int32_t new_y);
        void set_angle(int16_t new_angle);
        void set_skin_piece(uint8_t new_skin_piece);

        ~Player() = default;
    };
};

#endif // CLIENT_GAME_MODEL_PLAYER_H
