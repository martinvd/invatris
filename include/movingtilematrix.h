#ifndef MOVINGTILEMATRIX_H
#define MOVINGTILEMATRIX_H

class CMovingTileMatrix: public CFreeable {
    protected:
        void overwriteWith( CMovingTileMatrix *matrix );

        bool bAutoDelete;
        int iTurned;
    public:
        CMovingTileMatrix( bool bAutoDelete = true );
        ~CMovingTileMatrix();

        CMovingTile *m[5][5];

        void turn90();
};

#endif // MOVINGTILEMATRIX_H
