#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include "include/const.h"
#include "include/display.h"
#include "include/map.h"

#include "include/visualobject.h"

#include <math.h>

CDisplay *d;
Map *myMap;

#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))


class CMovingTile: public CFreeable {
    public:
        long x;
        long y;
};

CMovingTile *pMovingTile;

double iTime = 0;

void gameiter( double dDelta ) {
    iTime += dDelta;
    if ( int(iTime) >= 1 ) {
        iTime = 0;
        myMap->changeTileType( pMovingTile->x, pMovingTile->y, TILE_EMPTY );

        pMovingTile->y = MIN( MAP_HEIGHT - 1, pMovingTile->y + 1 );
        myMap->changeTileType( pMovingTile->x, pMovingTile->y, TILE_MOVABLE );
    }
}


/// main loop
int main ( int argc, char** argv ) {
    d = new CDisplay( "FreeManTetris", MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE );

    if ( !d->hasErrors() ) {
    } else {
        return 1;
    }

    // 16x16 images:
    CVisualObject *red = new CVisualImage( "red.bmp" );
    CVisualObject *green = new CVisualImage( "green.bmp" );
    CVisualObject *blue = new CVisualImage( "blue.bmp" );

    myMap = new Map( MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, red, green, blue );
    d->addVisualObject( 0, 0, myMap );

    pMovingTile = new CMovingTile();
    pMovingTile->x = 1;
    pMovingTile->y = 1;
    myMap->changeTileType( 1, 1, TILE_MOVABLE );

    d->setIterationfunc( gameiter );

    d->gameloop();

    delete pMovingTile;

    delete red;
    delete green;
    delete blue;

    delete myMap;

    delete d;

    return 0;
}
