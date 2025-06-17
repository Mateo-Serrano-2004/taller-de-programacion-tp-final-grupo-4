#include "cs2d_app.h"

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <variant>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Color.hh>
#include <SDL2pp/Point.hh>

#include "common/definitions.h"
#include "common/asset_addresser.h"

#include "client/net/client_protocol.h"

#include "context/context_manager.h"
#include "context/in_game_context.h"
#include "context/menu_context.h"
#include "context/pick_role_context.h"
#include "context/shop_context.h"
#include "context/end_of_game_context.h"

#include "asset/asset_loader.h"
#include "asset/asset_manager.h"
#include "asset/asset_generator.h"
#include "asset/font_id.h"

#include "controller/game_controller.h"
#include "controller/base_controller.h"

#include "utils/enum_translator.h"

App::CS2DApp::CS2DApp(Shared<Net::ClientProtocol> protocol): App::Application() {
    Model::EnumTranslator::build();
    auto window = make_shared<SDL2pp::Window>(
        "In Game",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480,
        0
    );
    auto renderer = make_shared<SDL2pp::Renderer>(*window, -1, SDL_RENDERER_ACCELERATED);
    renderer->SetLogicalSize(640, 480);

    auto asset_manager = make_shared<Model::AssetManager>(renderer);
    auto asset_loader = make_shared<Model::AssetLoader>(asset_manager, renderer);
    asset_loader->load_all_textures();

    context_manager = make_shared<Context::ContextManager>();
    auto game_controller = make_shared<Controller::GameController>(
        window, renderer, asset_manager, context_manager, protocol
    );

    auto weak_game_controller = Weak<Controller::GameController>(game_controller);
    game_controller->set_self_pointer(weak_game_controller);

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
