#ifndef CLIENT_GAME_ASSET_TEXTURE_ID_H
#define CLIENT_GAME_ASSET_TEXTURE_ID_H

namespace Model {
enum TextureID {
    // Skins from 0x00
    SPRITE_CT1 = 0x00,
    SPRITE_CT2 = 0x01,
    SPRITE_CT3 = 0x02,
    SPRITE_CT4 = 0x03,
    SPRITE_T1 = 0x04,
    SPRITE_T2 = 0x05,
    SPRITE_T3 = 0x06,
    SPRITE_T4 = 0x07,

    // Weapons from 0x10
    SPRITE_GLOCK = 0x10,
    SPRITE_AWP = 0x11,
    SPRITE_AK47 = 0x12,
    SPRITE_M3 = 0x13,
    SPRITE_BOMB = 0x14,
    SPRITE_KNIFE = 0x15,
    DROPPED_GLOCK = 0x16,
    DROPPED_AWP = 0x17,
    DROPPED_AK47 = 0x18,
    DROPPED_M3 = 0x19,
    DROPPED_BOMB = 0x20,

    // HUD textures from 0x40
    HUD_NUMS = 0x40,
    HUD_SYMBOLS = 0x41,
    HUD_AK47 = 0x42,
    HUD_AWP = 0x43,
    HUD_GLOCK = 0x44,
    HUD_KNIFE = 0x45,
    HUD_M3 = 0x46,

    // Special textures
    FOV = 0xC0,
    BOMB_EXPLOSION = 0xC1,
    NO_TEXTURE = 0xFF
};
};

#endif  // CLIENT_GAME_ASSET_TEXTURE_ID_H
