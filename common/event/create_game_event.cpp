#include "create_game_event.h"

#include <string>

std::string Model::CreateGameEvent::get_party_name() const { return party_name; }

std::string Model::CreateGameEvent::get_map_name() const { return map_name; }
