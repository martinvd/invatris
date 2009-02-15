#include "visualobject.h"

CVisualObject::CVisualObject( long iWidth, long iHeight ) : CFreeable::CFreeable() {
    surface = NULL;

    width   = iWidth;
    height  = iHeight;
}

CVisualObject::~CVisualObject() {
    deleteSurface();
}

void CVisualObject::deleteSurface() {
    if ( surface != NULL ) {
        SDL_FreeSurface( surface );

        surface = NULL;
    }
}

SDL_Surface *CVisualObject::getSurface() {
    return surface;
}

void CVisualObject::displayOn( SDL_Surface *pParentSurface, SDL_Rect *pCoords ) {
    SDL_BlitSurface( this->surface, NULL, pParentSurface, pCoords );
}


//-----------------------------------------------------------------------------

CVisualContainer::CVisualContainer( long iWidth, long iHeight ) : CVisualObject::CVisualObject( iWidth, iHeight ) {
}

CVisualContainer::~CVisualContainer() {
    clearVector();
}

void CVisualContainer::clearVector() {
    unsigned int c = lstPositionedObjects.size() - 1;
    for ( unsigned int i = 0; i < c; i++ ) {
        delete lstPositionedObjects.at(i);
    }

    lstPositionedObjects.clear();
}

void CVisualContainer::displayPositionedObjects() {
    CPositionedObject *obj = NULL;

    unsigned int c = lstPositionedObjects.size();
    for ( unsigned int i = 0; i < c; i++ ) {
        obj = lstPositionedObjects[i];
        if ( obj != NULL ) {
            obj->object->displayOn( this->surface, &obj->coords );
        }
    }
}

void CVisualContainer::displayPositionedObjects( SDL_Surface *pParentSurface, SDL_Rect *pCoords ) {
    SDL_Rect copyRect;
    CPositionedObject *obj = NULL;

    unsigned int c = lstPositionedObjects.size();
    for ( unsigned int i = 0; i < c; i++ ) {
        obj = lstPositionedObjects[i];
        if ( obj != NULL ) {
            copyRect.x = pCoords->x + obj->coords.x;
            copyRect.y = pCoords->y + obj->coords.y;

            obj->object->displayOn( pParentSurface, &copyRect );
        }
    }
}

CPositionedObject *CVisualContainer::addVisualObject( long x, long y, CVisualObject *object ) {
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

//-----------------------------------------------------------------------------

CVisualImage::CVisualImage() : CVisualObject::CVisualObject() {
    sFilenameUsed = "";
}

CVisualImage::CVisualImage( std::string sFilename ) : CVisualObject::CVisualObject() {
    loadFromFile( sFilename );
}

CVisualImage::~CVisualImage() {
}

void CVisualImage::loadFromFile( std::string sFilename ) {
    deleteSurface();

    sFilenameUsed = sFilename;
    SDL_Surface *surfLoadedImage = NULL;

    surfLoadedImage = SDL_LoadBMP( sFilename.c_str() );
    if ( surfLoadedImage != NULL ) {
        surface = SDL_DisplayFormat( surfLoadedImage );

        SDL_FreeSurface( surfLoadedImage );
    }

    height = surface->h;
    width  = surface->w;
}
