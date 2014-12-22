#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <math.h>

#include "include/const.h"
#include "include/display.h"
#include "include/map.h"
#include "include/visualimage.h"
#include "include/movingtile.h"
#include "tetrisobject.h"
#include "movingtilematrix.h"
#include "visualobject.h"
#include "visualcontainer.h"

CDisplay *d;
Map *myMap;

#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

class CTetrisObject_A: public CTetrisObject {
    public:
        CTetrisObject_A( long x, long y ) : CTetrisObject::CTetrisObject( x, y ) {
            matrix->m[2][1] = new CMovingTile( x - 1, y );
            matrix->m[2][2] = new CMovingTile( x, y );
            matrix->m[2][3] = new CMovingTile( x + 1, y );
            matrix->m[3][3] = new CMovingTile( x + 1, y + 1 );

            typeChange( TILE_MOVABLE );
        }
};

class CTetrisObject_B: public CTetrisObject {
    public:
        CTetrisObject_B( long x, long y ) : CTetrisObject::CTetrisObject( x, y ) {
            matrix->m[2][0] = new CMovingTile( x - 2, y );
            matrix->m[2][1] = new CMovingTile( x - 1, y );
            matrix->m[2][2] = new CMovingTile( x, y );
            matrix->m[2][3] = new CMovingTile( x + 1, y );
            matrix->m[2][4] = new CMovingTile( x + 2, y );

            typeChange( TILE_MOVABLE );
        }
};

class CTetrisObject_C: public CTetrisObject {
    public:
        CTetrisObject_C( long x, long y ) : CTetrisObject::CTetrisObject( x, y ) {
            matrix->m[2][1] = new CMovingTile( x - 1, y );
            matrix->m[2][2] = new CMovingTile( x, y );
            matrix->m[2][3] = new CMovingTile( x + 1, y );
            matrix->m[3][2] = new CMovingTile( x, y + 1 );

            typeChange( TILE_MOVABLE );
        }
};

class CTetrisObject_D: public CTetrisObject {
    public:
        CTetrisObject_D( long x, long y ) : CTetrisObject::CTetrisObject( x, y ) {
            matrix->m[2][1] = new CMovingTile( x - 1, y );
            matrix->m[2][2] = new CMovingTile( x, y );
            matrix->m[3][1] = new CMovingTile( x - 1, y + 1 );
            matrix->m[3][2] = new CMovingTile( x, y + 1 );

            typeChange( TILE_MOVABLE );
        }

        void turn() {
            // dont turn
        }
};

std::vector<CTetrisObject *> lstMovingTetrisObjects;

double iTime = 0;
bool bDone1 = false;
bool bDone2 = false;

void gameiter( double dDelta ) {

    iTime += dDelta;
    if ( iTime >= 0.1 ) {
        iTime = 0;

        for ( unsigned int i = 0; i < lstMovingTetrisObjects.size(); i++ ) {
            CTetrisObject *pObject = lstMovingTetrisObjects.at(i);

            if ( (i == 1) && !bDone1 ) {
                pObject->turn();
                bDone1 = true;
            } else if ( (i == 2) && !bDone2 ) {
                pObject->turn();
                pObject->turn();
                pObject->turn();
                bDone2 = true;
            } else if (i == 3) {
                pObject->turn();
            }
            pObject->moveDown();

        }

        for ( unsigned int i = 0; i < MAP_HEIGHT; i++ ) {
            if ( myMap->checkLine( i ) ) {
                myMap->removeRow( i );
            }
        }
    }
}

/// main loop
int main ( int argc, char** argv ) {
    // init display
    d = new CDisplay( "FreeManTetris", 640, 480 );

    if ( d->hasErrors() ) {
        return 1;
    }

    // 16x16 images:
    CVisualObject *red = new CVisualImage( "res/red.bmp" );
    CVisualObject *green = new CVisualImage( "res/green.bmp" );
    CVisualObject *blue = new CVisualImage( "res/blue.bmp" );

    // init game map
    myMap = new Map( MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, red, green, blue );
    d->addVisualObject( 100, 20, myMap );

    d->setIterationfunc( gameiter );

    lstMovingTetrisObjects.push_back( new CTetrisObject_A( 8, 2 ) );
    lstMovingTetrisObjects.push_back( new CTetrisObject_B( 6, 12 ) );
    lstMovingTetrisObjects.push_back( new CTetrisObject_C( 4, 4 ) );
    lstMovingTetrisObjects.push_back( new CTetrisObject_D( 11, 4 ) );
    lstMovingTetrisObjects.push_back( new CTetrisObject_C( 1, 2 ) );
    lstMovingTetrisObjects.push_back( new CTetrisObject_C( 13, 4 ) );

    // init game loop
    d->gameloop();

    // init freedom
    delete red;
    delete green;
    delete blue;

    delete myMap;

    delete d;

    return 0;
}
