#include "visualobject.h"

CVisualObject::CVisualObject() : CFreeable::CFreeable() {
    surface = NULL;
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


//-----------------------------------------------------------------------------

CVisualContainer::CVisualContainer() : CVisualObject::CVisualObject() {

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
            SDL_BlitSurface( obj->object->getSurface(), NULL, surface, &obj->coords );
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
}
