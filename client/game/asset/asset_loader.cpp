#include "asset_loader.h"

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Color.hh>
#include <SDL2pp/Point.hh>

#include "controller/game_controller.h"

#include "animation/animation_details.h"

#include "asset_manager.h"
#include "animation_id.h"
#include "texture_id.h"

void Model::AssetLoader::load_weapon_sprites() {
    manager->load_texture(
        Model::TextureID::SPRITE_AK47, addresser.get_weapon_sprite_path(weapon_sprites[0])
    );
    manager->load_texture(
        Model::TextureID::SPRITE_AWP, addresser.get_weapon_sprite_path(weapon_sprites[1])
    );
    manager->load_texture(
        Model::TextureID::SPRITE_BOMB, addresser.get_weapon_sprite_path(weapon_sprites[2])
    );
    manager->load_texture(
        Model::TextureID::SPRITE_GLOCK, addresser.get_weapon_sprite_path(weapon_sprites[3])
    );
    manager->load_texture(
        Model::TextureID::SPRITE_KNIFE, addresser.get_weapon_sprite_path(weapon_sprites[4])
    );
    manager->load_texture(
        Model::TextureID::SPRITE_M3, addresser.get_weapon_sprite_path(weapon_sprites[5])
    );
}

void Model::AssetLoader::load_player_sprites() {
    manager->load_texture(
        Model::TextureID::SPRITE_CT1, addresser.get_player_sprite_path(player_sprites[0])
    );
    manager->load_texture(
        Model::TextureID::SPRITE_CT2, addresser.get_player_sprite_path(player_sprites[1])
    );
    manager->load_texture(
        Model::TextureID::SPRITE_CT3, addresser.get_player_sprite_path(player_sprites[2])
    );
    manager->load_texture(
        Model::TextureID::SPRITE_CT4, addresser.get_player_sprite_path(player_sprites[3])
    );
    manager->load_texture(
        Model::TextureID::SPRITE_T1, addresser.get_player_sprite_path(player_sprites[4])
    );
    manager->load_texture(
        Model::TextureID::SPRITE_T2, addresser.get_player_sprite_path(player_sprites[5])
    );
    manager->load_texture(
        Model::TextureID::SPRITE_T3, addresser.get_player_sprite_path(player_sprites[6])
    );
    manager->load_texture(
        Model::TextureID::SPRITE_T4, addresser.get_player_sprite_path(player_sprites[7])
    );
}

void Model::AssetLoader::load_hud_texture(Model::TextureID id, int index) {
    SDL2pp::Surface surface(addresser.get_hud_resource(hud_textures[index]));

    surface.SetColorKey(
        true,
        SDL_MapRGB(surface.Get()->format, 0, 0, 0)
    );

    auto texture = make_shared<SDL2pp::Texture>(*renderer, surface);

    manager->load_texture(id, texture);
}

void Model::AssetLoader::load_hud_textures() {
    load_hud_texture(Model::TextureID::HUD_NUMS, 0);
    load_hud_texture(Model::TextureID::HUD_SYMBOLS, 1);
}

void Model::AssetLoader::load_fov() {
    manager->load_texture(Model::TextureID::FOV, generator.generate_fov());
}

void Model::AssetLoader::load_animations() {
    auto animation = generator.generate_animation({
        addresser.get_animation_path("muzzle-fire/muzzle_01.png"),
        addresser.get_animation_path("muzzle-fire/muzzle_02.png"),
        addresser.get_animation_path("muzzle-fire/muzzle_03.png"),
        addresser.get_animation_path("muzzle-fire/muzzle_04.png"),
        addresser.get_animation_path("muzzle-fire/muzzle_05.png")
    });
    manager->load_animation(
        Model::AnimationID::MUZZLE_FIRE,
        Model::AnimationDetails(5, 1, 5, 5, animation)
    );
}

Model::AssetLoader::AssetLoader(Shared<AssetManager> manager, Shared<SDL2pp::Renderer> renderer)
: player_sprites({
    "ct1.bmp", "ct2.bmp", "ct3.bmp",
    "ct4.bmp", "t1.bmp",  "t2.bmp",
    "t3.bmp",  "t4.bmp"}),
  weapon_sprites({
    "ak47.bmp", "awp.bmp", "bomb_d.bmp",
    "glock.bmp", "knife.bmp", "m3.bmp"
  }),
  hud_textures({
    "hud_nums.bmp", "hud_symbols.bmp"
  }),
  manager(manager),
  renderer(renderer),
  generator(renderer) {}

void Model::AssetLoader::load_all_textures() {
    load_weapon_sprites();
    load_player_sprites();
    load_hud_textures();
    load_fov();
    load_animations();
};
