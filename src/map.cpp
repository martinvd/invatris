// Game map class

#include <iostream>
#include <fstream>
#include <string>
#include "..\include\map.h"

Map::Map() {
    map_width = 0;
    map_height = 0;
}

Map::~Map() {
}

/// map laden vanuit bestand
bool Map::load(const char *filename) {

    char c;

    int height_x = 0;
    int height_y = 0;

    std::ifstream mapfile (filename, std::ios::in);

    if (mapfile.is_open()) {

        int line_nr = 0;
        while (mapfile.get(c)) {


        }

        mapfile.close();
    }

    return 0;
}
