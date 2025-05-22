#include "assets.h"

#include <string>

std::string get_texture_path(const std::string& texture_name) {
    return std::string(TEXTURES_ROOT) + texture_name;
}

std::string get_sound_path(const std::string& sound_name) {
    return std::string(SOUNDS_ROOT) + sound_name;
}
