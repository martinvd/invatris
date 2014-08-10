#ifndef MOVINGTILE_H
#define MOVINGTILE_H

#include "freeable.h"

class CMovingTile: public CFreeable {
    public:
        long x;
        long y;

        CMovingTile( long x, long y );
};

#endif // MOVINGTILE_H
