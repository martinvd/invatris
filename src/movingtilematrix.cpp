#include "movingtilematrix.h"

void CMovingTileMatrix::overwriteWith( CMovingTileMatrix *matrix ) {
    for ( int i = 0; i < 5; i++ ) {
        for ( int j = 0; j < 5; j++ ) {
            this->m[i][j] = matrix->m[i][j];
        }
    }
}

CMovingTileMatrix::CMovingTileMatrix( bool bAutoDelete = true ) : CFreeable::CFreeable() {
    this->bAutoDelete = bAutoDelete;
    iTurned = 0;

    for ( int i = 0; i < 5; i++ ) {
        for ( int j = 0; j < 5; j++ ) {
            m[i][j] = NULL;
        }
    }
}

CMovingTileMatrix::~CMovingTileMatrix() {
    if ( bAutoDelete ) {
        for ( int i = 0; i < 5; i++ ) {
            for ( int j = 0; j < 5; j++ ) {
                delete m[i][j];
            }
        }
    }
}

void CMovingTileMatrix::turn90() {
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
