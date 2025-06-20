#ifndef CLIENT_GAME_INTERFACE_FIXED_H
#define CLIENT_GAME_INTERFACE_FIXED_H

#include "render/camera.h"

class Fixed {
protected:
    View::Camera camera;

public:
    Fixed() = default;

    void fix(const View::Camera& new_camera);
    const View::Camera& get_fixation() const;

    virtual ~Fixed() = default;
};

#endif  // CLIENT_GAME_INTERFACE_FIXED_H
