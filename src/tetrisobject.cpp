#include "tetrisobject.h"

CTetrisObject::CTetrisObject( long x, long y ) : CFreeable::CFreeable() {
    iCenterX = x;
    iCenterY = y;

    matrix = new CMovingTileMatrix();

    bIsMoving = true;
}

CTetrisObject::~CTetrisObject() {
    delete matrix;
}

virtual void CTetrisObject::typeChange( unsigned int iType ) {
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

virtual void CTetrisObject::moveDown() {
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

virtual void CTetrisObject::turn() {
    if ( bIsMoving ) {
        typeChange( TILE_EMPTY );

        matrix->turn90();

        typeChange( TILE_MOVABLE );
    }
}
