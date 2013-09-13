#ifndef POSITIONEDOBJECT_H
#define POSITIONEDOBJECT_H

#include "freeable.h"
#include "visualobject.h"

#ifdef __APPLE__
    #include <SDL/SDL.h>
#else
    #include <SDL.h>
#endif

class CPositionedObject: public CFreeable {
    public:
        SDL_Rect coords;
        CVisualObject *object;
};

#endif // POSITIONEDOBJECT_H
