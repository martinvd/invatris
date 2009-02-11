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
            CBlokje *pBlokje = new CBlokje();
            pBlokje->iType = TILE_EMPTY;
            gameMap[i][j] = pBlokje;
        }
    }
}

void Map::removeRow(unsigned int y) {
    for(unsigned int i = 0; i <= y; i++) {
        for(unsigned int j = 0; j <= MAP_WIDTH; j++) {
            CBlokje *pBlokje = gameMap[i][j];
            if (pBlokje->iType != TILE_MOVABLE) {
                pBlokje->iType = i > 0 ? pBlokje->iType : 0;
            }

        }
    }
}

CBlokje *Map::getTile(unsigned int x, unsigned int y) {
    return gameMap[y][x];
}
