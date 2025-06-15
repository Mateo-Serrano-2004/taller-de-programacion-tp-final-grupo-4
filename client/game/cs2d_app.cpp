#include "cs2d_app.h"

#include <vector>
#include <string>
#include <memory>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Color.hh>
#include <SDL2pp/Point.hh>

#include "common/definitions.h"

#include "context/context_manager.h"
#include "context/in_game_context.h"
#include "context/menu_context.h"
#include "context/pick_role_context.h"
#include "context/shop_context.h"
#include "context/end_of_game_context.h"

#include "asset/asset_manager.h"
#include "asset/asset_generator.h"
#include "asset/asset_addresser.h"
#include "asset/font_id.h"

#include "controller/game_controller.h"
#include "controller/base_controller.h"

#include "client/net/client_protocol.h"

const std::vector<std::string> player_sprites = {
    "ct1.bmp", "ct2.bmp", "ct3.bmp",
    "ct4.bmp", "t1.bmp",  "t2.bmp",
    "t3.bmp",  "t4.bmp"
};

const std::vector<std::string> weapon_sprites = {
    "ak47.bmp", "awp.bmp", "bomb_d.bmp",
    "glock.bmp", "knife.bmp", "m3.bmp"
};

const std::vector<std::string> hud_textures = {
    "hud_nums.bmp", "hud_symbols.bmp"
};

void App::CS2DApp::load_weapon_sprites(Shared<Model::AssetManager> asset_manager) {
    Model::AssetAddresser asset_addresser;

    asset_manager->load_texture(
        Model::TextureID::SPRITE_AK47, asset_addresser.get_weapon_sprite_path(weapon_sprites[0])
    );
    asset_manager->load_texture(
        Model::TextureID::SPRITE_AWP, asset_addresser.get_weapon_sprite_path(weapon_sprites[1])
    );
    asset_manager->load_texture(
        Model::TextureID::SPRITE_BOMB, asset_addresser.get_weapon_sprite_path(weapon_sprites[2])
    );
    asset_manager->load_texture(
        Model::TextureID::SPRITE_GLOCK, asset_addresser.get_weapon_sprite_path(weapon_sprites[3])
    );
    asset_manager->load_texture(
        Model::TextureID::SPRITE_KNIFE, asset_addresser.get_weapon_sprite_path(weapon_sprites[4])
    );
    asset_manager->load_texture(
        Model::TextureID::SPRITE_M3, asset_addresser.get_weapon_sprite_path(weapon_sprites[5])
    );
}

void App::CS2DApp::load_player_sprites(Shared<Model::AssetManager> asset_manager) {
    Model::AssetAddresser asset_addresser;

    asset_manager->load_texture(
        Model::TextureID::SPRITE_CT1, asset_addresser.get_player_sprite_path(player_sprites[0])
    );
    asset_manager->load_texture(
        Model::TextureID::SPRITE_CT2, asset_addresser.get_player_sprite_path(player_sprites[1])
    );
    asset_manager->load_texture(
        Model::TextureID::SPRITE_CT3, asset_addresser.get_player_sprite_path(player_sprites[2])
    );
    asset_manager->load_texture(
        Model::TextureID::SPRITE_CT4, asset_addresser.get_player_sprite_path(player_sprites[3])
    );
    asset_manager->load_texture(
        Model::TextureID::SPRITE_T1, asset_addresser.get_player_sprite_path(player_sprites[4])
    );
    asset_manager->load_texture(
        Model::TextureID::SPRITE_T2, asset_addresser.get_player_sprite_path(player_sprites[5])
    );
    asset_manager->load_texture(
        Model::TextureID::SPRITE_T3, asset_addresser.get_player_sprite_path(player_sprites[6])
    );
    asset_manager->load_texture(
        Model::TextureID::SPRITE_T4, asset_addresser.get_player_sprite_path(player_sprites[7])
    );
}

void App::CS2DApp::load_hud_texture(
    Shared<Model::AssetManager> asset_manager,
    Shared<SDL2pp::Renderer> renderer,
    const std::string& texture_name,
    Model::TextureID texture_id
) {
    Model::AssetAddresser asset_addresser;

    SDL2pp::Surface surface(asset_addresser.get_hud_resource(texture_name));

    surface.SetColorKey(
        true,
        SDL_MapRGB(surface.Get()->format, 0, 0, 0)
    );

    auto texture = make_shared<SDL2pp::Texture>(*renderer, surface);

    asset_manager->load_texture(
        texture_id, texture
    );
}

void App::CS2DApp::load_hud_textures(
    Shared<Model::AssetManager> asset_manager,
    Shared<SDL2pp::Renderer> renderer
) {
    load_hud_texture(asset_manager, renderer, hud_textures[0], Model::TextureID::HUD_NUMS);
    load_hud_texture(asset_manager, renderer, hud_textures[1], Model::TextureID::HUD_SYMBOLS);
}

void App::CS2DApp::load_generated_textures(Shared<Model::AssetManager> asset_manager,
                                    Shared<SDL2pp::Renderer> renderer) {
    View::AssetGenerator asset_generator(renderer);
    asset_manager->load_texture(Model::TextureID::FOV, asset_generator.generate_fov());
}

App::CS2DApp::CS2DApp(Shared<Net::ClientProtocol> protocol): App::Application() {
    auto window = make_shared<SDL2pp::Window>(
        "In Game",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480,
        0
    );
    auto renderer = make_shared<SDL2pp::Renderer>(*window, -1, SDL_RENDERER_ACCELERATED);
    renderer->SetLogicalSize(640, 480);
    
    auto asset_manager = make_shared<Model::AssetManager>(renderer);
    load_weapon_sprites(asset_manager);
    load_player_sprites(asset_manager);
    load_hud_textures(asset_manager, renderer);
    load_generated_textures(asset_manager, renderer);

    context_manager = make_shared<Context::ContextManager>();
    auto game_controller = make_shared<Controller::GameController>(
        window, renderer, asset_manager, context_manager, protocol
    );
    auto weak_game_controller = Weak<Controller::GameController>(game_controller);
    game_controller->set_self_pointer(weak_game_controller);
    game_controller->build_game_state_manager();

    auto in_game_context = make_shared<Context::InGameContext>(weak_game_controller);
    auto menu_context = make_shared<Context::MenuContext>(weak_game_controller);
    auto pick_role_context = make_shared<Context::PickRoleContext>(weak_game_controller);
    auto shop_context = make_shared<Context::ShopContext>(weak_game_controller);
    auto end_of_game_context = make_shared<Context::EndOfGameContext>(weak_game_controller);

    context_manager->add_context(in_game_context);
    context_manager->add_context(menu_context);
    context_manager->add_context(pick_role_context);
    context_manager->add_context(shop_context);
    context_manager->add_context(end_of_game_context);

    context_manager->set_current_context("pick-role");

    controller = std::static_pointer_cast<Controller::BaseController>(game_controller);
}
