#include "visualimage.h"

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
        height = surface->h;
        width  = surface->w;
        SDL_FreeSurface( surfLoadedImage );
    } else {
        printf("Error loading resource: %s\n", SDL_GetError());
    }
}
