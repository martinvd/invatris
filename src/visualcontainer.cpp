#include "visualcontainer.h"

CVisualContainer::CVisualContainer( long iWidth, long iHeight ) : CVisualObject::CVisualObject( iWidth, iHeight ) {
}

CVisualContainer::~CVisualContainer() {
    clearVector();
}

void CVisualContainer::clearVector() {
    // free positioned objects from array
    unsigned int c = lstPositionedObjects.size() - 1;
    for ( unsigned int i = 0; i < c; i++ ) {
        delete lstPositionedObjects.at(i);
    }

    // clear the positioned objects array
    lstPositionedObjects.clear();
}

void CVisualContainer::displayPositionedObjects() {
    CPositionedObject *obj = NULL;

    // loop through positioned objects
    unsigned int c = lstPositionedObjects.size();
    for ( unsigned int i = 0; i < c; i++ ) {
        obj = lstPositionedObjects[i];
        if ( obj != NULL ) {
            // place positioned objects on the container surface
            obj->object->displayOn( this->surface, &obj->coords );
        }
    }
}

void CVisualContainer::displayPositionedObjects( SDL_Surface *pParentSurface, SDL_Rect *pCoords ) {
    SDL_Rect copyRect;
    CPositionedObject *obj = NULL;

    // loop through positioned objects
    unsigned int c = lstPositionedObjects.size();
    for ( unsigned int i = 0; i < c; i++ ) {
        obj = lstPositionedObjects[i];
        if ( obj != NULL ) {
            copyRect.x = pCoords->x + obj->coords.x;
            copyRect.y = pCoords->y + obj->coords.y;

            // place positioned objects on the selected surface
            obj->object->displayOn( pParentSurface, &copyRect );
        }
    }
}

CPositionedObject* CVisualContainer::addVisualObject( long x, long y, CVisualObject *object ) {
    CPositionedObject *pObj = new CPositionedObject();
    pObj->coords.x = x;
    pObj->coords.y = y;

    pObj->object = object;

    lstPositionedObjects.push_back( pObj );

    return pObj;
}

void CVisualContainer::displayOn( SDL_Surface *pParentSurface, SDL_Rect *pCoords ) {
    if ( this->surface != NULL ) {
        // eerst op het eigen surface weergeven
        this->displayPositionedObjects();

        // daarna onze surface blitten naar het parent-surface
        SDL_BlitSurface( this->surface, NULL, pParentSurface, pCoords );
    } else {
        // indien we zelf geen surface hebben worden de objects in deze container direct weergegeven op de meegegeven surface

        this->displayPositionedObjects( pParentSurface, pCoords );
    }
}
