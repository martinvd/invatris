// Game map class

#ifndef MAP_H
#define MAP_H

#include "freeable.h"

class Map: public CFreeable {

    protected:
        int map_width;       // map width in blocks
        int map_height;      // map height in blocks

    public:
        Map();
        ~Map();

        bool load(const char *filename);           // load map from file
        void setTile(int x, int y, int type);      // set map tile type

        bool display();                            // display map
};

#endif
