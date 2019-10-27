#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{}

void ShaderProgram::reload()
{
    createShader(vertexID, GL_VERTEX_SHADER, vertexShader);
    createShader(fragmentID, GL_FRAGMENT_SHADER, fragmentShader);
    createShader(geometryID, GL_GEOMETRY_SHADER, geometryShader);

    programID = glCreateProgram();
    glAttachShader(programID,vertexID);
    glAttachShader(programID,geometryID);
    glAttachShader(programID,fragmentID);

    glLinkProgram(programID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
    glDeleteShader(geometryID);
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::createShader(unsigned int& shaderID, int shaderType, std::string shader)
{
    const char* shaderCode = shader.c_str();
    shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID,1,&shaderCode,NULL);
    glCompileShader(shaderID);

    int success;
    char infolog[512];
    glGetShaderiv(shaderID,GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, infolog);
        std::cerr<<"Error in compiling shader"<<std::endl<<infolog<<std::endl<<shader<<std::endl;
    }
}

void ShaderProgram::use()
{
    glUseProgram(programID);
}

void ShaderProgram::unuse()
{
    glUseProgram(0);
}

void ShaderProgram::setUniform(std::string uniformName, float* matrix)
{
    const char* cUniformName = uniformName.c_str();
    int uniformLoc = glGetUniformLocation(programID, cUniformName);
    glUniformMatrix4fv(uniformLoc,1,false,matrix);
}

void ShaderProgram::setUniform(std::string uniformName, float value)
{
    const char* cUniformName = uniformName.c_str();
    int uniformLoc = glGetUniformLocation(programID, cUniformName);
    glUniform1f(uniformLoc,value);
}
