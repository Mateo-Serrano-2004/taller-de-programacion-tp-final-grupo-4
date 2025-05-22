#ifndef CLIENT_GAME_MODEL_PLAYER_H
#define CLIENT_GAME_MODEL_PLAYER_H

#include <cstdint>

namespace Model {
    class Player {
    private:
        uint16_t x;
        uint16_t y;
        uint16_t skin_id;
        uint8_t skin_piece;

        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;

    public:
        Player(uint16_t x, uint16_t y, uint16_t skin_id);

        Player(Player&&) = default;
        Player& operator=(Player&&) = default;

        uint16_t get_x() const;
        uint16_t get_y() const;
        uint16_t get_skin_id() const;
        uint8_t get_skin_piece() const;

        void set_x(uint16_t new_x);
        void set_y(uint16_t new_y);
        void set_skin_piece(uint8_t new_skin_piece);

        ~Player() = default;
    };
};

#endif // CLIENT_GAME_MODEL_PLAYER_H
