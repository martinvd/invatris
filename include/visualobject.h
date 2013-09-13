#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include "freeable.h"
#include <string>
#include <vector>

#ifdef __APPLE__
    #include <SDL/SDL.h>
#else
    #include <SDL.h>
#endif

class CVisualObject : public CFreeable {
    protected:
        long width;
        long height;

        SDL_Surface *surface;
        void deleteSurface();

    public:
        CVisualObject( long iWidth = 0, long iHeight = 0 );
        ~CVisualObject();

        SDL_Surface *getSurface();

        virtual void displayOn( SDL_Surface *pParentSurface, SDL_Rect *pCoords );
};

#endif // VISUALOBJECT_H
