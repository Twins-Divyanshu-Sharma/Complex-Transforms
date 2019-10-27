#include "Grid.h"

Grid::Grid(int scale)
{
    this->scale = scale;
    setMesh(scale);
    generate();
}

Grid::~Grid()
{
    delete[] mesh.vertexCoords;
}

void Grid::setMesh(int scale)
{
    int j=0;
    mesh.size = ((2*scale+1)*2*2)*2;
    // 2*scale for (-scale to -1) and ( 0 th line) and (1 to scale)
    // this is doubled for 2 points in each line
    // again doubled because every points have 2 vertices
    // and finally again doubled to repeat whole procedure for vertical line as well

    mesh.vertexCoords = new float[mesh.size];
    for(int i=-scale; i<=scale; i++)
    {
        mesh.vertexCoords[j++] = -scale;
        mesh.vertexCoords[j++] = i;
        mesh.vertexCoords[j++] = scale;
        mesh.vertexCoords[j++] = i;
    }
    for(int i=-scale; i<=scale; i++)
    {
        mesh.vertexCoords[j++] = i;
        mesh.vertexCoords[j++] = -scale;
        mesh.vertexCoords[j++] = i;
        mesh.vertexCoords[j++] = scale;
    }
}

void Grid::generate()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.size*sizeof(float), mesh.vertexCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

int Grid::getVao()
{
    return vao;
}

int Grid::getMeshSize()
{
    return mesh.size;
}

int Grid::getScale()
{
    return scale;
}
