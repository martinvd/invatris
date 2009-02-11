// Game map class

#ifndef MAP_H
#define MAP_H

#include "const.h"
#include "freeable.h"

#include "visualobject.h"

class CBlokje: public CFreeable {
    public:
        unsigned int iType;
        CPositionedObject *ptrObject;
};

class Map: public CFreeable {
    protected:
        CBlokje *gameMap[MAP_HEIGHT][MAP_WIDTH];

    public:
        Map();
        ~Map();

        void clearMap();
        void removeRow(unsigned int y);
        CBlokje *getTile(unsigned int x, unsigned int y);
};

#endif
