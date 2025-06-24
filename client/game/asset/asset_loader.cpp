#include "asset_loader.h"

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2pp/Color.hh>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Texture.hh>

#include "animation/animation_details.h"
#include "common/DTO/config_dto.h"
#include "controller/game_controller.h"

#include "animation_id.h"
#include "asset_manager.h"
#include "cursor_id.h"
#include "sound_id.h"
#include "texture_id.h"

void Model::AssetLoader::load_weapon_sprites() {
    manager->load_texture(Model::TextureID::SPRITE_AK47,
                          addresser.get_weapon_sprite_path(weapon_sprites[0]));
    manager->load_texture(Model::TextureID::SPRITE_AWP,
                          addresser.get_weapon_sprite_path(weapon_sprites[1]));
    manager->load_texture(Model::TextureID::SPRITE_BOMB,
                          addresser.get_weapon_sprite_path(weapon_sprites[2]));
    manager->load_texture(Model::TextureID::SPRITE_GLOCK,
                          addresser.get_weapon_sprite_path(weapon_sprites[3]));
    manager->load_texture(Model::TextureID::SPRITE_KNIFE,
                          addresser.get_weapon_sprite_path(weapon_sprites[4]));
    manager->load_texture(Model::TextureID::SPRITE_M3,
                          addresser.get_weapon_sprite_path(weapon_sprites[5]));
}

void Model::AssetLoader::load_dropped_weapon_sprites() {
    load_from_surface(Model::TextureID::DROPPED_AK47,
                      addresser.get_weapon_sprite_path(dropped_weapon_sprites[0]));
    load_from_surface(Model::TextureID::DROPPED_AWP,
                      addresser.get_weapon_sprite_path(dropped_weapon_sprites[1]));
    load_from_surface(Model::TextureID::DROPPED_BOMB,
                      addresser.get_weapon_sprite_path(dropped_weapon_sprites[2]));
    load_from_surface(Model::TextureID::DROPPED_GLOCK,
                      addresser.get_weapon_sprite_path(dropped_weapon_sprites[3]));
    load_from_surface(Model::TextureID::DROPPED_M3,
                      addresser.get_weapon_sprite_path(dropped_weapon_sprites[4]));
}

void Model::AssetLoader::load_player_sprites() {
    manager->load_texture(Model::TextureID::SPRITE_CT1,
                          addresser.get_player_sprite_path(player_sprites[0]));
    manager->load_texture(Model::TextureID::SPRITE_CT2,
                          addresser.get_player_sprite_path(player_sprites[1]));
    manager->load_texture(Model::TextureID::SPRITE_CT3,
                          addresser.get_player_sprite_path(player_sprites[2]));
    manager->load_texture(Model::TextureID::SPRITE_CT4,
                          addresser.get_player_sprite_path(player_sprites[3]));
    manager->load_texture(Model::TextureID::SPRITE_T1,
                          addresser.get_player_sprite_path(player_sprites[4]));
    manager->load_texture(Model::TextureID::SPRITE_T2,
                          addresser.get_player_sprite_path(player_sprites[5]));
    manager->load_texture(Model::TextureID::SPRITE_T3,
                          addresser.get_player_sprite_path(player_sprites[6]));
    manager->load_texture(Model::TextureID::SPRITE_T4,
                          addresser.get_player_sprite_path(player_sprites[7]));
}

void Model::AssetLoader::load_from_surface(Model::TextureID id, const std::string& path) {
    SDL2pp::Surface surface(path);

    surface.SetColorKey(true, SDL_MapRGB(surface.Get()->format, 0, 0, 0));

    auto texture = make_shared<SDL2pp::Texture>(*renderer, surface);

    manager->load_texture(id, texture);
}

void Model::AssetLoader::load_hud_textures() {
    load_from_surface(Model::TextureID::HUD_NUMS, addresser.get_hud_resource(hud_textures[0]));
    load_from_surface(Model::TextureID::HUD_SYMBOLS, addresser.get_hud_resource(hud_textures[1]));
    load_from_surface(Model::TextureID::HUD_AK47, addresser.get_hud_resource(hud_textures[2]));
    load_from_surface(Model::TextureID::HUD_AWP, addresser.get_hud_resource(hud_textures[3]));
    load_from_surface(Model::TextureID::HUD_GLOCK, addresser.get_hud_resource(hud_textures[4]));
    load_from_surface(Model::TextureID::HUD_KNIFE, addresser.get_hud_resource(hud_textures[5]));
    load_from_surface(Model::TextureID::HUD_M3, addresser.get_hud_resource(hud_textures[6]));
}

void Model::AssetLoader::load_fov() {
    manager->load_texture(Model::TextureID::FOV, generator.generate_fov());
}

void Model::AssetLoader::load_bomb_animation() {
    manager->load_texture(Model::TextureID::BOMB_EXPLOSION,
                          addresser.get_animation_path("explosion.png"));
    auto bomb_animation_texture = manager->get_texture(Model::TextureID::BOMB_EXPLOSION);
    manager->load_animation(Model::AnimationID::BOMB_EXPLOSION,
                            Model::AnimationDetails(5, 5, 23, 40, bomb_animation_texture));
}

void Model::AssetLoader::load_shot_animation() {
    auto animation = generator.generate_animation(
            {addresser.get_animation_path("muzzle-fire/muzzle_01.png"),
             addresser.get_animation_path("muzzle-fire/muzzle_02.png"),
             addresser.get_animation_path("muzzle-fire/muzzle_03.png"),
             addresser.get_animation_path("muzzle-fire/muzzle_04.png"),
             addresser.get_animation_path("muzzle-fire/muzzle_05.png")});
    manager->load_animation(Model::AnimationID::MUZZLE_FIRE,
                            Model::AnimationDetails(5, 1, 5, 5, animation));
}

void Model::AssetLoader::load_animations() {
    load_bomb_animation();
    load_shot_animation();
}

void Model::AssetLoader::load_sounds() {
    manager->load_sound(Model::SoundID::BOMB_DEFUSED, sounds[0]);
    manager->load_sound(Model::SoundID::BOMB_PLANTED, sounds[1]);
    manager->load_sound(Model::SoundID::AK47_FIRE, sounds[2]);
    manager->load_sound(Model::SoundID::AWP_FIRE, sounds[3]);
    manager->load_sound(Model::SoundID::BOMB_EXPLOSION, sounds[4]);
    manager->load_sound(Model::SoundID::GLOCK_FIRE, sounds[5]);
    manager->load_sound(Model::SoundID::KNIFE_SLASH, sounds[6]);
    manager->load_sound(Model::SoundID::M3_FIRE, sounds[7]);
    manager->load_sound(Model::SoundID::RELOAD_SOUND, sounds[8]);
    manager->load_sound(Model::SoundID::START_ROUND_CT, sounds[9]);
    manager->load_sound(Model::SoundID::START_ROUND_TT, sounds[10]);
    manager->load_sound(Model::SoundID::WINNER_CT, sounds[11]);
    manager->load_sound(Model::SoundID::WINNER_TT, sounds[12]);
    manager->load_sound(Model::SoundID::HIT_SOUND, sounds[13]);
    manager->load_sound(Model::SoundID::DEATH_SOUND, sounds[14]);
}

void Model::AssetLoader::load_cursor() {
    manager->load_cursor(Model::CursorID::RED, addresser.get_cursor_path("pointer.bmp"),
                         SDL2pp::Rect(48, 0, 48, 48));
    manager->set_cursor(Model::CursorID::RED, SDL2pp::Point(10, 10));
}

Model::AssetLoader::AssetLoader(Shared<AssetManager> manager, Shared<SDL2pp::Renderer> renderer,
                                const DTO::ConfigDTO& config):
        player_sprites({"ct1.bmp", "ct2.bmp", "ct3.bmp", "ct4.bmp", "t1.bmp", "t2.bmp", "t3.bmp",
                        "t4.bmp"}),
        weapon_sprites({"ak47.bmp", "awp.bmp", "bomb_d.bmp", "glock.bmp", "knife.bmp", "m3.bmp"}),
        dropped_weapon_sprites({"dropped_ak47.bmp", "dropped_awp.bmp", "bomb_d.bmp",
                                "dropped_glock.bmp", "dropped_m3.bmp"}),
        hud_textures({"hud_nums.bmp", "hud_symbols.bmp", "ak47_k.bmp", "awp_k.bmp", "glock_k.bmp",
                      "knife_k.bmp", "m3_k.bmp"}),
        sounds({"radio/bomb-defused.ogg", "radio/bomb-planted.ogg", "weapons/ak47.wav",
                "weapons/awp.wav", "weapons/bomb.wav", "weapons/glock.wav", "weapons/knife.wav",
                "weapons/m3.wav", "weapons/reload.wav", "radio/letsgo.ogg", "radio/moveout.ogg",
                "radio/ctwin.ogg", "radio/terwin.ogg", "players/hit-player.wav",
                "players/death.wav"}),
        manager(manager),
        renderer(renderer),
        config(config),
        generator(renderer, config) {}

void Model::AssetLoader::load_all_textures() {
    load_dropped_weapon_sprites();
    load_weapon_sprites();
    load_player_sprites();
    load_hud_textures();
    load_fov();
    load_animations();
    load_sounds();
    load_cursor();
}
