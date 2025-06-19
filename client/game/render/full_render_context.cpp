#include "full_render_context.h"

#include <cstdint>
#include <map>
#include <list>

#include <SDL2pp/Texture.hh>

#include "model/rendered_player.h"

#include "animation/muzzle_fire_animation.h"

Model::FullRenderContext::FullRenderContext(
        uint16_t time_left,
        Shared<View::RenderedPlayer> ref_player,
        const std::map<short_id_t, Shared<View::RenderedPlayer>>& players,
        const std::list<Shared<View::MuzzleFireAnimation>> fires,
        Shared<SDL2pp::Texture> map,
        const View::Camera& camera)
        : Model::RenderContext(time_left, ref_player),
          players(players), fires(fires), map(map), camera(camera) {}
