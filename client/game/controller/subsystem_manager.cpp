#include "subsystem_manager.h"

#include <SDL2/SDL.h>

Controller::SubsystemManager::SubsystemManager(
    int sdl_flags,
    int frequency,
    Uint16 format,
    int channels,
    int chunksize
): sdl(sdl_flags),
   ttf(),
   mixer(frequency, format, channels, chunksize) {}