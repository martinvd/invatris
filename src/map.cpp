// Game map class

#include "const.h"
#include "map.h"

Map::Map() : CFreeable::CFreeable() {
    clearMap();
}

Map::~Map() {
}

void Map::clearMap() {
    for(unsigned int i = 0; i <= MAP_HEIGHT; i++) {
        for(unsigned int j = 0; j <= MAP_WIDTH; j++) {
            gameMap[i][j] = TILE_EMPTY;
        }
    }
}

void Map::removeRow(unsigned int y) {
    for(unsigned int i = 0; i <= y; i++) {
        for(unsigned int j = 0; j <= MAP_WIDTH; j++) {

            if (gameMap[i][j] != TILE_MOVABLE) {
                gameMap[i][j] = i > 0 ? gameMap[i - 1][j] : 0;
            }

        }
    }
}

unsigned int Map::getTile(unsigned int x, unsigned int y) {
    return gameMap[y][x];
}
