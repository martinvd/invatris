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
