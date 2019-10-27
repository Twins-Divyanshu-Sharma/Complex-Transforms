#ifndef GRID_H
#define GRID_H

#include "allgl.h"

class Grid
{
    public:
        Grid(int);
        ~Grid();
        int getVao();
        int getMeshSize();
        int getScale();

    private:
        struct Mesh
        {
            int size;
            float* vertexCoords;
        }mesh;

        int scale;
        unsigned int vao, vbo;
        void generate();
        void setMesh(int);
};

#endif
