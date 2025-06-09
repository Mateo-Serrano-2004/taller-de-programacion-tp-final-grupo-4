#ifndef CLIENT_GAME_MODEL_RENDERED_PLAYER_H
#define CLIENT_GAME_MODEL_RENDERED_PLAYER_H

#include <cstdint>
#include <string>

#include "common/definitions.h"
#include "common/role_id.h"
#include "common/texture_id.h"
#include "common/weapon_id.h"
#include "common/model/player.h"
#include "common/model/weapon.h"
#include "common/model/vector_2d.h"

namespace View {
class RenderedPlayer: public Model::Player {
protected:
    Model::TextureID sprite_id;
    short_id_t sprite_piece;
    Model::TextureID weapon_sprite_id;

    short_id_t get_sprite_piece_from_weapon();

public:
    RenderedPlayer(Model::Player&& player);

    Model::TextureID get_sprite_id() const;
    short_id_t get_sprite_piece() const;
    Model::TextureID get_weapon_sprite_id() const;

    void set_sprite_id(Model::TextureID new_sprite_id);
    void set_sprite_piece(short_id_t new_sprite_piece);
    void set_weapon_sprite_id(Model::TextureID new_weapon_sprite_id);

    ~RenderedPlayer() override = default;
};
};

#endif // CLIENT_GAME_MODEL_RENDERED_PLAYER_H
