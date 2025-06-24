#include "game_handler.h"

#include "controller/game_controller.h"

Controller::GameHandler::GameHandler(Weak<GameController> controller): controller(controller) {}
