#include "display.h"

#ifdef __APPLE__
    #include <SDL/SDL.h>
#else
    #include <SDL.h>
#endif

#include "const.h"

CDisplay::CDisplay( const char *sCaption, long iWidth, long iHeight ) : CVisualContainer::CVisualContainer( iWidth, iHeight )
{
    this->sWindowCaption = sCaption;
    this->iterationfunc = NULL;

    bHasError = false;
    bShouldBeRunning = true;
    init();
}

CDisplay::~CDisplay()
{
}

void CDisplay::checkKeys() {
    Uint8 *keystates = SDL_GetKeyState( NULL );
    if( keystates[SDLK_ESCAPE] ) {
        bShouldBeRunning = false;
    }
}

void CDisplay::stop() {
    bShouldBeRunning = false;
}

void CDisplay::setIterationfunc( gameiterationfunc func ) {
    this->iterationfunc = func;
}

void CDisplay::gameloop() {
    unsigned long iDelta = 0;
    unsigned long iNewTime = SDL_GetTicks();
    unsigned long iOldTime = iNewTime;

    SDL_Event event;
    while ( bShouldBeRunning ) {
        while( SDL_PollEvent( &event ) ) {
            if( event.type == SDL_QUIT ) {
                bShouldBeRunning = true;
            }
        }

        checkKeys();

        displayPositionedObjects();

        if ( iDelta > 0 ) {
            if ( iterationfunc != NULL ) {
                iterationfunc( iDelta / 1000.0 );
            }
        }

        if ( SDL_Flip( surface ) == -1 ) {
            bShouldBeRunning = false;
            bHasError = true;
            break;
        }

        iNewTime = SDL_GetTicks();
        iDelta = iNewTime - iOldTime;
        iOldTime = iNewTime;
    }
}

bool CDisplay::hasErrors() {
    return bHasError;
}

void CDisplay::init() {
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        bHasError = true;
        return;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    surface = SDL_SetVideoMode( width, height, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !surface ) {
        printf("Unable to set video resolution: %s\n", SDL_GetError());
        bHasError = true;
        return;
    }

    SDL_WM_SetCaption( sWindowCaption.c_str(), NULL);
}
