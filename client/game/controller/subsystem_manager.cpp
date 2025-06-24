#include "subsystem_manager.h"

#include <SDL2/SDL.h>
#include <SDL2pp/Mixer.hh>

Controller::SubsystemManager::SubsystemManager(int sdl_flags, int frequency, Uint16 format,
                                               int channels, int chunksize):
        sdl(sdl_flags), ttf(), mixer(frequency, format, channels, chunksize) {
    mixer.AllocateChannels(32);
}

SDL2pp::Mixer& Controller::SubsystemManager::get_mixer() { return mixer; }
