#ifndef CLIENT_GAME_MIZZLE_FIRE_ANIMATION_H
#define CLIENT_GAME_MIZZLE_FIRE_ANIMATION_H

#include <cstdint>

#include "common/definitions.h"
#include "render/camera.h"

#include "animation.h"

namespace Controller {
class GameController;
};

namespace View {
class RenderedPlayer;

class MuzzleFireAnimation: public Animation {
protected:
    Camera camera;
    Shared<RenderedPlayer> player;

    short_id_t player_id;

    int get_fire_distance();
    void render_muzzle();

public:
    MuzzleFireAnimation(Weak<Controller::GameController> controller, short_id_t player_id);

    short_id_t get_player_id() const;

    void set_camera(const Camera& new_camera);
    void set_player(Shared<RenderedPlayer> new_player);

    void end();

    void render() override;

    ~MuzzleFireAnimation() override = default;
};
};  // namespace View

#endif  // CLIENT_GAME_MIZZLE_FIRE_ANIMATION_H
