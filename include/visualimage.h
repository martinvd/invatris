#ifndef VISUALIMAGE_H
#define VISUALIMAGE_H

#include "visualobject.h"

class CVisualImage: public CVisualObject {
    protected:
        std::string sFilenameUsed;
    public:
        CVisualImage();
        CVisualImage( std::string sFilename );
        ~CVisualImage();

        void loadFromFile( std::string sFilename );
};

#endif // VISUALIMAGE_H
