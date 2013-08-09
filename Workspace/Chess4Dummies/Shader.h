#ifndef _SHADER_
#define _SHADER_

#include "Common.h"
#include <GL/glew.h>
#include <GL/glut.h>


namespace View {

class Shader 
{
public:
    Shader();
    Shader(const std::string& vertShader, const std::string fragShader );
    Shader( const Shader& other );

    ~Shader();
    void operator = ( const Shader& other );

    void init();

    inline GLuint getShaderID() const
    {
        return _shaderID;
    }

    void use();

protected:
    void createShaders();

    GLuint       _vertShader;
    GLuint       _fragShader;
    GLuint       _shaderID;
    std::string  _vertShaderSrc;
    std::string  _fragShaderSrc;
};

}

#endif