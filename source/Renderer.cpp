#include "Renderer.h"

Renderer::Renderer()
{
    orthogonalMatrix = new float[16];
    shaderProgram = new ShaderProgram();
    shaderProgram->reload();
}

Renderer::~Renderer()
{
    delete[] orthogonalMatrix;
}

void Renderer::setOrthogonalProjection(float l, float r, float b, float t, float n, float f)
{
    float ortho[] =
    {
        2.0f/(r-l),          0,             0,          0,
            0,          2.0f/(t-b),         0,          0,
            0,               0,          2.0f/(n-f),    0,
        -(r+l)/(r-l),   -(t+b)/(t-b),    -(f+n)/(f-n),  1
    };

    int size = *(&ortho+1) - ortho;

    for(int i=0; i<size; i++)
    {
        orthogonalMatrix[i] = ortho[i];
    }
}

void Renderer::render(Grid& grid)
{
   shaderProgram->use();
   glBindVertexArray(grid.getVao());
   glEnableVertexAttribArray(0);
   shaderProgram->setUniform("ortho",orthogonalMatrix);
   shaderProgram->setUniform("scale",grid.getScale());
   shaderProgram->setUniform("supply",next);
   glDrawArrays(GL_LINES, 0, grid.getMeshSize());
   glDisableVertexAttribArray(0);
   glBindVertexArray(0);
   shaderProgram->unuse();
}

void Renderer::setNext(float next)
{
    this->next = next;
}

void Renderer::reload()
{
    shaderProgram->reload();
}
