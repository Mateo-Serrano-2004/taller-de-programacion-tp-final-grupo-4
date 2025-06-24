#include "subsystem_manager.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/Mixer.hh>

Controller::SubsystemManager::SubsystemManager(int sdl_flags, int frequency, Uint16 format,
                                               int channels, int chunksize):
        sdl(sdl_flags), ttf(), mixer(frequency, format, channels, chunksize) {
    (void)Mix_Init(MIX_INIT_OGG);
    mixer.AllocateChannels(32);
}

SDL2pp::Mixer& Controller::SubsystemManager::get_mixer() { return mixer; }
