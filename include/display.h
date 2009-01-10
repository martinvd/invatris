#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "freeable.h"
#include "visualobject.h"
#include <string>
#include <vector>

class CDisplay: public CVisualContainer
{
    protected:
        bool bHasError;
        bool bShouldBeRunning;

        void init();

        void checkKeys();

    public:
        CDisplay();
        ~CDisplay();

        void gameloop();
        void stop();

        bool hasErrors();
};

#endif // __DISPLAY_H
