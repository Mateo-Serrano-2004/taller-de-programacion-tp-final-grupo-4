#ifndef TILE_TYPE_H
#define TILE_TYPE_H

#include <vector>

enum TileType { NOT_COLLIDABLE = 0, COLLIDABLE = 1, CT_SPAWN = 2, TT_SPAWN = 3, BOMB_SITE = 4 };

using MapMatrix = std::vector<std::vector<TileType>>;

#endif  // TILE_TYPE_H
