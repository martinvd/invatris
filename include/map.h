// Game map class

#ifndef MAP_H
#define MAP_H

#include "const.h"
#include "freeable.h"

class Map: public CFreeable {

    private:
        unsigned int gameMap[MAP_HEIGHT][MAP_WIDTH];

    public:
        Map();
        ~Map();

        void clearMap();
        void removeRow(unsigned int y);
        unsigned int getTile(unsigned int x, unsigned int y);
};

#endif
