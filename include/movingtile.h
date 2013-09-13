#ifndef MOVINGTILE_H
#define MOVINGTILE_H

#include "freeable.h"

class CMovingTile: public CFreeable {
    public:
        long x;
        long y;

        CMovingTile( long x, long y ) : CFreeable::CFreeable();
};

#endif // MOVINGTILE_H
