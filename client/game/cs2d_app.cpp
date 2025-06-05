#include "cs2d_app.h"

#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <iostream>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Color.hh>
#include <SDL2pp/Point.hh>

#include "common/definitions.h"
#include "common/texture_id.h"

#include "context/context_manager.h"
#include "context/in_game_context.h"
#include "context/menu_context.h"

#include "asset/asset_manager.h"
#include "asset/asset_generator.h"
#include "asset/asset_addresser.h"
#include "asset/font_id.h"

#include "controller/game_controller.h"

#include "client/net/client_protocol.h"

const std::vector<std::string> paths = {"ct1.bmp", "ct2.bmp", "ct3.bmp",
                                        "ct4.bmp", "t1.bmp",  "t2.bmp",
                                        "t3.bmp",  "t4.bmp"};

void App::CS2DApp::load_sprites(Shared<Model::AssetManager> asset_manager, Shared<SDL2pp::Renderer> renderer) {
    Model::AssetAddresser asset_addresser;

    asset_manager->load_texture(Model::TextureID::SPRITE_CT1, asset_addresser.get_sprite_path(paths[0]));
    asset_manager->load_texture(Model::TextureID::SPRITE_CT2, asset_addresser.get_sprite_path(paths[1]));
    asset_manager->load_texture(Model::TextureID::SPRITE_CT3, asset_addresser.get_sprite_path(paths[2]));
    asset_manager->load_texture(Model::TextureID::SPRITE_CT4, asset_addresser.get_sprite_path(paths[3]));
    asset_manager->load_texture(Model::TextureID::SPRITE_T1, asset_addresser.get_sprite_path(paths[4]));
    asset_manager->load_texture(Model::TextureID::SPRITE_T2, asset_addresser.get_sprite_path(paths[5]));
    asset_manager->load_texture(Model::TextureID::SPRITE_T3, asset_addresser.get_sprite_path(paths[6]));
    asset_manager->load_texture(Model::TextureID::SPRITE_T4, asset_addresser.get_sprite_path(paths[7]));

    SDL2pp::Color dark_green(33, 42, 34, 255);
    SDL2pp::Color smooth_green(110, 120, 112, 255);

    View::AssetGenerator asset_generator(renderer);
    asset_manager->load_texture(Model::TextureID::FOV, asset_generator.generate_fov());
    asset_manager->load_texture(Model::TextureID::BG_DARK_GREEN, asset_generator.generate_plain_texture(dark_green));
    asset_manager->load_texture(Model::TextureID::BG_SMOOTH_GREEN, asset_generator.generate_plain_texture(smooth_green));
}

void App::CS2DApp::load_fonts(Shared<Model::AssetManager> asset_manager) {
    Model::AssetAddresser asset_addresser;
    asset_manager->load_font(
        Model::FontID::STANDARD,
        asset_addresser.get_font_path("liberationsans.ttf"),
        20
    );
}

App::CS2DApp::CS2DApp(Net::ClientProtocol* protocol): App::Application() {
    auto window = make_shared<SDL2pp::Window>(
        "In Game",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 460,
        SDL_WINDOW_SHOWN
    );
    auto renderer = make_shared<SDL2pp::Renderer>(*window, -1, SDL_RENDERER_ACCELERATED);

    renderer->SetDrawColor(255, 255, 255, 255);
    renderer->SetDrawBlendMode(SDL_BLENDMODE_BLEND);
    
    auto asset_manager = make_shared<Model::AssetManager>(renderer);
    load_sprites(asset_manager, renderer);
    load_fonts(asset_manager);

    context_manager = make_shared<Context::ContextManager>();
    controller = make_shared<Controller::GameController>(
        window, renderer, asset_manager, context_manager, protocol
    );

    auto in_game_context = make_shared<Context::InGameContext>(
        Weak<Controller::GameController>(
            std::static_pointer_cast<Controller::GameController>(controller)
        )
    );

    auto menu_context = make_shared<Context::MenuContext>(
        Weak<Controller::GameController>(
            std::static_pointer_cast<Controller::GameController>(controller)
        )
    );

    context_manager->add_context(in_game_context);
    context_manager->add_context(menu_context);

    context_manager->set_current_context("in-game");
}
