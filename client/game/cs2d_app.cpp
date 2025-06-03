#include "cs2d_app.h"

#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>

#include "common/definitions.h"

#include "context/context_manager.h"
#include "context/in_game_context.h"
#include "context/menu_context.h"
#include "texture/texture_storage.h"
#include "controller/game_controller.h"

#include "client/net/client_protocol.h"

const std::vector<std::string> paths = {"player/ct1.bmp", "player/ct2.bmp", "player/ct3.bmp",
                                        "player/ct4.bmp", "player/t1.bmp",  "player/t2.bmp",
                                        "player/t3.bmp",  "player/t4.bmp",  "player/vip.bmp"};

App::CS2DApp::CS2DApp(Net::ClientProtocol* protocol): App::Application() {
    auto window = make_shared<SDL2pp::Window>(
        "In Game",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 460,
        SDL_WINDOW_SHOWN
    );
    auto renderer = make_shared<SDL2pp::Renderer>(*window, -1, SDL_RENDERER_ACCELERATED);
    renderer->SetDrawColor(255, 255, 255, 255);

    auto texture_storage = make_shared<Model::TextureStorage>(Weak<SDL2pp::Renderer>(renderer));
    for (size_t i = 0; i < paths.size(); ++i) {
        texture_storage->load_texture(i, paths[i]);
    }

    context_manager = make_shared<Context::ContextManager>();
    controller = make_shared<Controller::GameController>(
        window, renderer, texture_storage, context_manager, protocol
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

    context_manager->set_current_context("menu");
}
