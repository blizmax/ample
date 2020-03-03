#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "VertexShader.h"
#include "Exception.h"
#include "Debug.h"
#include "Utils.h"

namespace ample::graphics::shaders
{
VertexShader::VertexShader(const std::string &filename, GLuint programId)
    : Shader(programId)
{
    DEBUG("Uploading vertex shader from" + filename);
    _shaderId = glCreateShader(GL_VERTEX_SHADER);
    exception::OpenGLException::handle();

    std::string vertexShaderCode;
    std::ifstream vertexShaderStream(filename);
    if (!vertexShaderStream.good())
    {
        throw exception::Exception(exception::exId::FILE_READ,
                                   exception::exType::CASUAL);
    }
    {
        std::stringstream sstr;
        sstr << vertexShaderStream.rdbuf();
        if (!sstr.good() || !vertexShaderStream.good())
        {
            throw exception::Exception(exception::exId::FILE_READ,
                                       exception::exType::CASUAL);
        }
        vertexShaderCode = sstr.str();
    }

    DEBUG("Compiling vertex shader from" + filename);
    {
        char const *vertexSourcePointer = vertexShaderCode.c_str();
        glShaderSource(_shaderId, 1, &vertexSourcePointer, NULL);
        glCompileShader(_shaderId);
        exception::OpenGLException::handle();
    }

    // Check Vertex Shader
    {
        GLint checkResult = GL_FALSE, infoLogLength;
        glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &checkResult);
        glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength > 0)
        {
            std::string vertexShaderErrorMessage;
            vertexShaderErrorMessage.resize(infoLogLength);
            glGetShaderInfoLog(_shaderId, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
            exception::OpenGLException::handle(vertexShaderErrorMessage);
        }
    }
    glAttachShader(_programId, _shaderId);
}

VertexShader::~VertexShader()
{
    glDetachShader(_programId, _shaderId);
    glDeleteShader(_shaderId);
}
} // namespace ample::graphics::shaders