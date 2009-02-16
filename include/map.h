// Game map class

#ifndef MAP_H
#define MAP_H

#include "const.h"
#include "freeable.h"

#include "visualobject.h"

class CBlokje: public CFreeable {
    public:
        CBlokje();
        ~CBlokje();

        unsigned int iType;
        CPositionedObject *ptrObject;
};

class Map: public CVisualContainer {
    protected:
        CBlokje *gameMap[MAP_HEIGHT][MAP_WIDTH];

        CVisualObject *pVisObjRed;
        CVisualObject *pVisObjGreen;
        CVisualObject *pVisObjBlue;

    public:
        Map( long iWidth, long iHeight, CVisualObject *pRed, CVisualObject *pGreen, CVisualObject *pBlue );
        ~Map();

        void clearMap();
        void removeRow(unsigned int y);

        bool checkLine( unsigned int y );

        CBlokje *getTile(unsigned int x, unsigned int y);

        CBlokje *changeTileType( unsigned int x, unsigned int y, unsigned int iNewType );
};

#endif
