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

        CMovingTile( long x, long y ) : CFreeable::CFreeable() {
            this->x = x;
            this->y = y;
        }
};

class CMovingTileMatrix: public CFreeable {
    protected:
        void overwriteWith( CMovingTileMatrix *matrix ) {
            for ( int i = 0; i < 5; i++ ) {
                for ( int j = 0; j < 5; j++ ) {
                    this->m[i][j] = matrix->m[i][j];
                }
            }
        }

        bool bAutoDelete;
        int iTurned;
    public:
        CMovingTile *m[5][5];

        CMovingTileMatrix( bool bAutoDelete = true ) : CFreeable::CFreeable() {
            this->bAutoDelete = bAutoDelete;
            iTurned = 0;

            for ( int i = 0; i < 5; i++ ) {
                for ( int j = 0; j < 5; j++ ) {
                    m[i][j] = NULL;
                }
            }
        }

        ~CMovingTileMatrix() {
            if ( bAutoDelete ) {
                for ( int i = 0; i < 5; i++ ) {
                    for ( int j = 0; j < 5; j++ ) {
                        delete m[i][j];
                    }
                }
            }
        }

        void turn90() {
            CMovingTileMatrix *copy = new CMovingTileMatrix( false );

            for ( int i = 0; i < 5; i++ ) {
                copy->m[0][4-i] = this->m[i][0];
                copy->m[1][4-i] = this->m[i][1];
                copy->m[2][4-i] = this->m[i][2];
                copy->m[3][4-i] = this->m[i][3];
                copy->m[4][4-i] = this->m[i][4];
            }

            this->overwriteWith( copy );

            delete copy;
        }
};

class CTetrisObject: public CFreeable {
    protected:
        long iCenterX;
        long iCenterY;

        CMovingTileMatrix *matrix;

        bool bIsMoving;
    public:
        CTetrisObject( long x, long y ) : CFreeable::CFreeable() {
            iCenterX = x;
            iCenterY = y;

            matrix = new CMovingTileMatrix();

            bIsMoving = true;
        }
        ~CTetrisObject() {
            delete matrix;
        }

        virtual void typeChange( unsigned int iType ) {
            long iStartX = iCenterX - 2;
            long iStartY = iCenterY - 2;

            for ( int i = 0; i < 5; i++ ) {
                for ( int j = 0; j < 5; j++ ) {
                    if ( matrix->m[i][j] != NULL ) {
                        myMap->changeTileType( iStartX + j, iStartY + i, iType );
                    }
                }
            }
        }

        virtual void moveDown() {
            if ( bIsMoving ) {
                typeChange( TILE_EMPTY );

                iCenterY++;

                long iStartX = iCenterX - 2;
                long iStartY = iCenterY - 2;
                for ( int i = 0; i < 5; i++ ) {
                    for ( int j = 0; j < 5; j++ ) {
                        if ( matrix->m[i][j] != NULL ) {
                            if ( iStartY + i + 1 == MAP_HEIGHT ) {
                                bIsMoving = false;
                                break;
                            } else {
                                CBlokje *b = myMap->getTile( iStartX + j, iStartY + i + 1 );

                                if ( b->iType == TILE_FILLED ) {
                                    bIsMoving = false;
                                    break;
                                }
                            }
                        }
                    }

                    if ( !bIsMoving ) {
                        break;
                    }
                }

                if ( bIsMoving ) {
                    typeChange( TILE_MOVABLE );
                } else {
                    typeChange( TILE_FILLED );
                }
            }
        }

        virtual void turn() {
            if ( bIsMoving ) {
                typeChange( TILE_EMPTY );

                matrix->turn90();

                typeChange( TILE_MOVABLE );
            }
        }
};

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
                //pObject->turn();
                //pObject->turn();
                //pObject->turn();
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
    d = new CDisplay( "FreeManTetris", 640, 480 );

    if ( !d->hasErrors() ) {
    } else {
        return 1;
    }

    // 16x16 images:
    CVisualObject *red = new CVisualImage( "red.bmp" );
    CVisualObject *green = new CVisualImage( "green.bmp" );
    CVisualObject *blue = new CVisualImage( "blue.bmp" );

    myMap = new Map( MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, red, green, blue );
    d->addVisualObject( 100, 20, myMap );

    d->setIterationfunc( gameiter );

    lstMovingTetrisObjects.push_back( new CTetrisObject_A( 8, 2 ) );
    lstMovingTetrisObjects.push_back( new CTetrisObject_B( 6, 12 ) );
    lstMovingTetrisObjects.push_back( new CTetrisObject_C( 4, 4 ) );
    lstMovingTetrisObjects.push_back( new CTetrisObject_D( 11, 4 ) );
    lstMovingTetrisObjects.push_back( new CTetrisObject_C( 1, 2 ) );
    lstMovingTetrisObjects.push_back( new CTetrisObject_C( 13, 4 ) );

    d->gameloop();

    delete red;
    delete green;
    delete blue;

    delete myMap;

    delete d;

    return 0;
}
