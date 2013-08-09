#include "Board.h"


using namespace View;

View::Board::Board()
:DrawElement( DrawElement::BOARD )
{
    _texture = new Texture("data/board.bmp");
}

void View::Board::draw()
{
    _shader.use();
    _texture->use();
    
    GLint texture_location = glGetUniformLocation(_shader.getShaderID(), "tex");
    glUniform1i(texture_location, 1);

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void View::Board::createGeometry()
{
    glGenBuffers(1, &_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    GLfloat geometry[] = {
        1.0f, 1.0f, 0.0f,
       -1.0f, 1.0f, 0.0f,
        1.0f,-1.0f, 0.0f,
        1.0f,-1.0f, 0.0f,
       -1.0f, 1.0f, 0.0f,
       -1.0f,-1.0f, 0.0f,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(geometry), geometry, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

View::Board::~Board()
{

}
