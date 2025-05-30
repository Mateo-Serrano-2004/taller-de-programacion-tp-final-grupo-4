#ifndef CLIENT_ASSETS_H
#define CLIENT_ASSETS_H

#include <string>

// Defined when setting CMAKE_BUILD_TYPE to Debug
#ifdef DEBUG_MODE

#define TEXTURES_ROOT "assets/gfx/"
#define SOUNDS_ROOT "assets/sfx/"

#else

#define TEXTURES_ROOT "/var/cs2d_assets/gfx/"
#define SOUNDS_ROOT "/var/acs2d_ssets/sfx/"

#endif

std::string get_texture_path(const std::string& texture_name);
std::string get_sound_path(const std::string& texture_name);

#endif  // CLIENT_ASSETS_H
