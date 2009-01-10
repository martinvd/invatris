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

    CVisualObject *beans = new CVisualImage( "C:/Windows/Coffee Bean.bmp" );
    CVisualImage stones( "C:/Windows/Greenstone.bmp" );

    d.addVisualObject( 10, 10, beans );
    d.addVisualObject( 50, 50, &stones );
    d.addVisualObject( 100, 100, beans );

    d.gameloop();

    delete beans;


    return 0;
}
