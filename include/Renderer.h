#ifndef RENDERER_H
#define RENDERER_H

#include "Grid.h"
#include "ShaderProgram.h"

class Renderer
{
    public:
        Renderer();
        ~Renderer();

        void setOrthogonalProjection(float,float,float,float,float,float);
        void render(Grid&);
        void setNext(float);
        void reload();

    private:
        float* orthogonalMatrix;
        ShaderProgram* shaderProgram;
        float next;
};

#endif
