#include "pick_sprite_event.h"

#include "common/event_type.h"

Model::PickSpriteEvent::PickSpriteEvent(Model::TextureID sprite_id)
: Model::Event(Model::EventType::PICK_SKIN), sprite_id(sprite_id) {}

Model::TextureID Model::PickSpriteEvent::get_sprite_id() const { return sprite_id; }
