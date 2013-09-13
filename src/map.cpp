// Game map class

#include "const.h"
#include "map.h"

//----------------------------------------------------------------------------

CBlokje::CBlokje() : CFreeable::CFreeable() {
    this->iType     = 0;
    this->ptrObject = NULL;
}

CBlokje::~CBlokje() {
    delete this->ptrObject;
}

//----------------------------------------------------------------------------


Map::Map( long iWidth, long iHeight, CVisualObject *pRed, CVisualObject *pGreen, CVisualObject *pBlue ) : CVisualContainer::CVisualContainer( iWidth, iHeight ) {
    this->pVisObjRed        = pRed;
    this->pVisObjGreen      = pGreen;
    this->pVisObjBlue       = pBlue;

    clearMap();
}

Map::~Map() {
}

void Map::clearMap() {
    unsigned int xPos = 0;
    unsigned int yPos = 0;

    for(unsigned int y = 0; y < MAP_HEIGHT; y++) {
        for(unsigned int x = 0; x < MAP_WIDTH; x++) {
            CBlokje *pBlokje = new CBlokje();

            pBlokje->ptrObject = this->addVisualObject(xPos, yPos, this->pVisObjGreen );
            pBlokje->iType = TILE_EMPTY;

            xPos += TILE_SIZE;
            gameMap[y][x] = pBlokje;
        }

        xPos = 0;
        yPos += TILE_SIZE;
    }
}

bool Map::checkLine( unsigned int y ) {
    for(unsigned int x = 0; x < MAP_WIDTH; x++) {
        CBlokje *pBlokje = gameMap[y][x];
        if (pBlokje->iType != TILE_FILLED) {
            return false;
        }
    }

    return true;
}

void Map::removeRow(unsigned int iRow) {
    for(int y = iRow; y >= 0; y--) {
        for(unsigned int x = 0; x < MAP_WIDTH; x++) {
            CBlokje *pBlokjeA = getTile( x, y - 1 );
            //CBlokje *pBlokjeB = getTile( x, y );
            if ( pBlokjeA != NULL ) {
                changeTileType( x, y, pBlokjeA->iType );
            } else {
                changeTileType( x, y, TILE_EMPTY );
            }
        }
    }
}

CBlokje *Map::getTile(unsigned int x, unsigned int y) {
    if ( (x >= 0) && (x < MAP_WIDTH) && (y >= 0) && (y < MAP_HEIGHT) ) {
        return gameMap[y][x];
    }

    return NULL;
}

CBlokje *Map::changeTileType( unsigned int x, unsigned int y, unsigned int iNewType ) {
    CBlokje *pBlokje = getTile( x, y );

    if ( pBlokje != NULL ) {
        if ( pBlokje->iType != iNewType ) {
            if ( iNewType == TILE_EMPTY ) {
                pBlokje->ptrObject->object = this->pVisObjGreen;
            } else if ( iNewType == TILE_MOVABLE ) {
                pBlokje->ptrObject->object = this->pVisObjRed;
            } else if ( iNewType == TILE_FILLED ) {
                pBlokje->ptrObject->object = this->pVisObjBlue;
            }
            pBlokje->iType = iNewType;
        }
    }

    return pBlokje;
}
