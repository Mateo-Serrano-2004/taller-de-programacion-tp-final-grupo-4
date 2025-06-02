#ifndef CLIENT_GAME_ENTITY_PLAYER_H
#define CLIENT_GAME_ENTITY_PLAYER_H

#include <utility>

#include "rect_entity.h"

namespace Model {
class Player;
};

namespace View {
class Player : public RectEntity {
protected:
    Model::Player& player;

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    std::pair<uint16_t, uint16_t> get_skin_piece() const;

    
public:
    Player(Model::Player& player);

    void render(RenderContext& render_context) override;

    ~Player() override = default;
};
};

#endif // CLIENT_GAME_ENTITY_PLAYER_H
