#ifndef CLIENT_GAME_MIZZLE_FIRE_ANIMATION_H
#define CLIENT_GAME_MIZZLE_FIRE_ANIMATION_H

#include <cstdint>

#include "common/definitions.h"

#include "animation.h"

namespace Controller {
class GameController;
};

namespace View {
class RenderedPlayer;

class MuzzleFireAnimation: public Animation {
protected:
    short_id_t player_id;

    void render_muzzle(Shared<View::RenderedPlayer> player);

public:
    MuzzleFireAnimation(
        Weak<Controller::GameController> controller,
        short_id_t player_id
    );

    void render() override;

    ~MuzzleFireAnimation() override = default;
};
};

#endif // CLIENT_GAME_MIZZLE_FIRE_ANIMATION_H
