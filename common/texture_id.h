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

    // Weapons from 0x10
    SPRITE_GLOCK,
    SPRITE_AWP,
    SPRITE_AK47,
    SPRITE_M3,
    SPRITE_BOMB,
    SPRITE_KNIFE,

    // Custom backgrounds from 0x70

    // Special textures
    FOV = 0xC0,
    NO_TEXTURE = 0xFF
};
};

#endif // COMMON_TEXTURE_ID_H
