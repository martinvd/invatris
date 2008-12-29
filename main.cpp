#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "include\map.h"

/// main loop
int main ( int argc, char** argv ) {

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface *screen = SDL_SetVideoMode(320, 320, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if (!screen) {
        printf("Unable to set video resolution: %s\n", SDL_GetError());
        return 1;
    }

    SDL_WM_SetCaption("FreeMan", NULL);

    SDL_Delay(2000);    // 2 seconden pauze


    Map gamemap;

    gamemap.load("map.txt");

    return 0;
}
