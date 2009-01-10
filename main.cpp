#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include "include/display.h"
#include "include/map.h"

/// main loop
int main ( int argc, char** argv ) {

    CDisplay d;

    if ( !d.hasErrors() ) {
        Map gamemap;
        gamemap.load("map.txt");
    } else {
        return 1;
    }

    d.addVisualObject( 10, 10, new CVisualImage( "C:/Windows/Coffee Bean.bmp" ) );
    d.addVisualObject( 50, 50, new CVisualImage( "C:/Windows/Greenstone.bmp" ) );

    d.gameloop();

    return 0;
}
