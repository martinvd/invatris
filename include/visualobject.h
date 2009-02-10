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

class CVisualObject : public CFreeable
{
    protected:
        SDL_Surface *surface;
        void deleteSurface();

    public:
        CVisualObject();
        ~CVisualObject();

        SDL_Surface *getSurface();
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
        void clearVector();

    public:
        CVisualContainer();
        ~CVisualContainer();

        CPositionedObject *addVisualObject( long x, long y, CVisualObject *object );

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
