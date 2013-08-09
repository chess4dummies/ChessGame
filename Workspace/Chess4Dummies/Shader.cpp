#include "Shader.h"
#include "Common.h"

using namespace std;
using namespace View;

#include "HelperFuncs.h"

Shader::Shader()
{

}

Shader::Shader( const Shader& other )
{

}

Shader::Shader( const string& vertShader, const string fragShader )
{
    _vertShaderSrc = vertShader;
    _fragShaderSrc = fragShader;
}

Shader::~Shader()
{

}

void Shader::operator=( const Shader& other )
{

}

void Shader::createShaders()
{
    // create and compiler vertex shader
    _vertShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vSrc = _vertShaderSrc.c_str();
    const int vLength = _vertShaderSrc.size();
    glShaderSource(_vertShader, 1, &vSrc, &vLength);
    glCompileShader(_vertShader);
    if(!Helpers::check_shader_compile_status(_vertShader))
    {
        assert(0);
    }

    // create and compiler fragment shader
    _fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fSrc  = _fragShaderSrc.c_str();
    const int fLength = _fragShaderSrc.size();
    glShaderSource(_fragShader, 1, &fSrc, &fLength);
    glCompileShader(_fragShader);
    if(!Helpers::check_shader_compile_status(_fragShader))
    {
        assert(0);
    }

    // create program
    _shaderID = glCreateProgram();

    glAttachShader(_shaderID, _vertShader);
    glAttachShader(_shaderID, _fragShader);

    glLinkProgram(_shaderID);
    Helpers::check_program_link_status(_shaderID);
}

void Shader::init()
{
    createShaders();
}

void View::Shader::use()
{
    glUseProgram(_shaderID);
}
