#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include "include/const.h"
#include "include/display.h"
#include "include/map.h"

/// main loop
int main ( int argc, char** argv ) {

    CDisplay d;

    if ( !d.hasErrors() ) {
        Map gamemap();
    } else {
        return 1;
    }

    // 16x16 images:
    CVisualObject *red = new CVisualImage( "red.bmp" );
    CVisualObject *green = new CVisualImage( "green.bmp" );
    CVisualObject *blue = new CVisualImage( "blue.bmp" );
    //CVisualImage stones( "testtile.bmp" );

    //d.addVisualObject( 10, 10, beans );
    //d.addVisualObject( 50, 50, &stones );
    //d.addVisualObject( 100, 100, beans );

    int xPos = 0;
    int yPos = 0;
    for(int i = 0; i <= MAP_HEIGHT; i++) {
        for(int j = 0; j <= MAP_WIDTH; j++) {
            d.addVisualObject(xPos, yPos, green );
            xPos += TILE_SIZE;
        }
        xPos = 0;
        yPos += TILE_SIZE;
    }

    d.gameloop();

    delete red;
    delete green;
    delete blue;

    return 0;
}
