#ifndef COMMON_TEXTURE_ID_H
#define COMMON_TEXTURE_ID_H

namespace Model {
enum TextureID {
    // Skins from 0x00
    SPRITE_CT1 = 0x00,
    SPRITE_CT2 = 0x01,
    SPRITE_CT3 = 0x02,
    SPRITE_CT4 = 0x03,
    SPRITE_T1 = 0x04,
    SPRITE_T2 = 0x05,
    SPRITE_T3 = 0x05,
    SPRITE_T4 = 0x06,

    // Weapons from 0x20

    // Backgrounds from 0x40
    BG_DARK_GREEN = 0x10,
    BG_SMOOTH_GREEN = 0x11,

    // Custom backgrounds from 0x60

    // Special textures
    FOV = 0xC0
};
};

#endif // COMMON_TEXTURE_ID_H
