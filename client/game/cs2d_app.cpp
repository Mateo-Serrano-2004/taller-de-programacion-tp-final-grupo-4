#include "cs2d_app.h"

#include <memory>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Window.hh>

#include "asset/asset_loader.h"
#include "asset/asset_manager.h"
#include "client/net/client_protocol.h"
#include "common/DTO/config_dto.h"
#include "common/definitions.h"
#include "context/context_manager.h"
#include "context/in_game_context.h"
#include "context/loading_context.h"
#include "context/menu_context.h"
#include "context/pick_role_context.h"
#include "context/shop_context.h"
#include "context/stats_context.h"
#include "controller/base_controller.h"
#include "controller/game_controller.h"
#include "utils/enum_translator.h"

Shared<Controller::GameController> App::CS2DApp::set_up_graphics(
        Shared<Net::ClientProtocol> protocol) {
    auto config = std::get<DTO::ConfigDTO>(protocol->receive_variant());
    auto window =
            make_shared<SDL2pp::Window>("In Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                        config.width, config.height, SDL_WINDOW_RESIZABLE);
    auto renderer = make_shared<SDL2pp::Renderer>(*window, -1, SDL_RENDERER_ACCELERATED);
    renderer->SetLogicalSize(config.width, config.height);

    auto asset_manager = make_shared<Model::AssetManager>(&subsystem_manager, renderer, config);
    auto asset_loader = make_shared<Model::AssetLoader>(asset_manager, renderer, config);
    asset_loader->load_all_textures();

    context_manager = make_shared<Context::ContextManager>();
    auto game_controller = make_shared<Controller::GameController>(
            window, renderer, asset_manager, asset_loader, context_manager, protocol);

    auto weak_game_controller = Weak<Controller::GameController>(game_controller);
    game_controller->set_self_pointer(weak_game_controller);
    return game_controller;
}

void App::CS2DApp::set_up_contexts(Weak<Controller::GameController> game_controller) {
    auto in_game_context = make_shared<Context::InGameContext>(game_controller);
    auto menu_context = make_shared<Context::MenuContext>(game_controller);
    auto pick_role_context = make_shared<Context::PickRoleContext>(game_controller);
    auto shop_context = make_shared<Context::ShopContext>(game_controller);
    auto loading_context = make_shared<Context::LoadingContext>(game_controller);
    auto stats_context = make_shared<Context::StatsContext>(game_controller);

    context_manager->add_context(in_game_context);
    context_manager->add_context(menu_context);
    context_manager->add_context(pick_role_context);
    context_manager->add_context(shop_context);
    context_manager->add_context(loading_context);
    context_manager->add_context(stats_context);

    context_manager->set_current_context("loading");
}

App::CS2DApp::CS2DApp(Shared<Net::ClientProtocol> protocol): App::Application() {
    Model::EnumTranslator::build();
    auto game_controller = set_up_graphics(protocol);
    auto weak_game_controller = Weak<Controller::GameController>(game_controller);
    set_up_contexts(weak_game_controller);
    controller = std::static_pointer_cast<Controller::BaseController>(game_controller);
}
