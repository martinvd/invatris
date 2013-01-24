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

class CPositionedObject: public CFreeable {
    public:
        SDL_Rect coords;
        CVisualObject *object;
};

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

class CVisualImage: public CVisualObject {
    protected:
        std::string sFilenameUsed;
    public:
        CVisualImage();
        CVisualImage( std::string sFilename );
        ~CVisualImage();

        void loadFromFile( std::string sFilename );
};

#endif // VISUALOBJECT_H
