#ifndef TETRISOBJECT_H
#define TETRISOBJECT_H

#include "freeable.h"
#include "movingtilematrix.h"

class CTetrisObject: public CFreeable {
    protected:
        long iCenterX;
        long iCenterY;

        CMovingTileMatrix *matrix;

        bool bIsMoving;
    public:
        CTetrisObject( long x, long y );
        ~CTetrisObject();

        virtual void typeChange( unsigned int iType );
        virtual void moveDown();
        virtual void turn();
}

#endif // TETRISOBJECT_H
