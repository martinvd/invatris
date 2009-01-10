#include "display.h"

#ifdef __APPLE__
    #include <SDL/SDL.h>
#else
    #include <SDL.h>
#endif

CDisplay::CDisplay() : CVisualContainer::CVisualContainer()
{
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

void CDisplay::gameloop() {
    SDL_Event event;
    while ( bShouldBeRunning ) {
        while( SDL_PollEvent( &event ) ) {
            if( event.type == SDL_QUIT ) {
                bShouldBeRunning = true;
            }
        }

        checkKeys();

        displayPositionedObjects();

        if ( SDL_Flip( surface ) == -1 ) {
            bShouldBeRunning = false;
            bHasError = true;
            break;
        }
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
    surface = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !surface ) {
        printf("Unable to set video resolution: %s\n", SDL_GetError());
        bHasError = true;
        return;
    }

    SDL_WM_SetCaption("FreeMan", NULL);
}
