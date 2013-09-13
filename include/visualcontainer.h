#ifndef VISUALCONTAINER_H
#define VISUALCONTAINER_H

#include "visualobject.h"
#include "positionedobject.h"

class CVisualContainer: public CVisualObject {
    protected:
        std::vector<CPositionedObject *> lstPositionedObjects;
        void displayPositionedObjects();
        void displayPositionedObjects( SDL_Surface *pParentSurface, SDL_Rect *pCoords );
        void clearVector();

    public:
        CVisualContainer( long iWidth, long iHeight );
        ~CVisualContainer();

        CPositionedObject *addVisualObject( long x, long y, CVisualObject *object );

        void displayOn( SDL_Surface *pParentSurface, SDL_Rect *pCoords );
};

#endif // VISUALCONTAINER_H
