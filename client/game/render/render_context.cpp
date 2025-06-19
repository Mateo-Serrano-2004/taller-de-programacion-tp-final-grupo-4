#include "render_context.h"

#include <cstdint>

#include "model/rendered_player.h"

Model::RenderContext::RenderContext(uint16_t time_left, Shared<View::RenderedPlayer> ref_player)
: time_left(time_left), ref_player(ref_player) {}
