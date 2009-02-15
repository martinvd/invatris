#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "freeable.h"
#include "visualobject.h"
#include <string>
#include <vector>

typedef void (*gameiterationfunc)( double );

class CDisplay: public CVisualContainer
{
    protected:
        bool bHasError;
        bool bShouldBeRunning;

        void init();

        void checkKeys();

        std::string sWindowCaption;

        gameiterationfunc iterationfunc;

    public:
        CDisplay( const char *sCaption, long iWidth, long iHeight );
        ~CDisplay();

        void setIterationfunc( gameiterationfunc func );

        void gameloop();
        void stop();

        bool hasErrors();
};

#endif // __DISPLAY_H
