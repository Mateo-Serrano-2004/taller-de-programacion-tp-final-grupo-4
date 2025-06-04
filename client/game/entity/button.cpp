#include "button.h"

#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include "controller/base_controller.h"

View::Button::Button(short_id_t texture_id, Weak<Controller::BaseController> controller,
                     Pane* parent):
                     View::Pane(texture_id, controller, parent) {}

View::Button::Button(short_id_t texture_id, Weak<Controller::BaseController> controller):
                     View::Pane(texture_id, controller) {}
