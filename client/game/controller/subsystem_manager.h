#ifndef CLIENT_GAME_CONTROLLER_SUBSYSTEM_MANAGER_H
#define CLIENT_GAME_CONTROLLER_SUBSYSTEM_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDLTTF.hh>

namespace Controller {
class SubsystemManager {
private:
    SDL2pp::SDL sdl;
    SDL2pp::SDLTTF ttf;
    SDL2pp::Mixer mixer;

public:
    explicit SubsystemManager(int sdl_flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO,
                              int frequency = 44100, Uint16 format = MIX_DEFAULT_FORMAT,
                              int channels = 2, int chunksize = 8192);

    SDL2pp::Mixer& get_mixer();

    ~SubsystemManager() = default;
};
};  // namespace Controller

#endif  // CLIENT_GAME_CONTROLLER_SUBSYSTEM_MANAGER_H
