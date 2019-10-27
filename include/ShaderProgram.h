#ifndef SH_PROG
#define SH_PROG

#include <string>
#include "allgl.h"
#include "Shaders.h"
#include <iostream>

class ShaderProgram
{
    public:
        ShaderProgram();
        ~ShaderProgram();
        void use();
        void unuse();
        void setUniform(std::string, float*);
        void setUniform(std::string, float);
        void reload();

    private:
        unsigned int vertexID, geometryID, fragmentID, programID;
        void createShader(unsigned int&, int, std::string);
};

#endif
