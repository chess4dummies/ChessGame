#include "Board.h"
#include <src/glm/gtc/matrix_transform.hpp>


using namespace View;

View::Board::Board()
:DrawElement( DrawElement::BOARD )
{
    _textureList.reserve(MAX_TEXTURES);
    _textureList.resize(MAX_TEXTURES);
    _textureList[0] = new Texture("data/board.bmp");
    _textureList[1] = new Texture("data/board_bump.bmp");
}

static float trans = 90.0f;
void View::Board::draw()
{
    //trans += 5.0f;
     //face up
      {
        _textureList[0]->use();
        _textureList[1]->use();
        _modelMatrix = glm::mat4x4(1.0); 
        _modelMatrix = glm::translate(_modelMatrix, glm::vec3(0.0f, 0.0f, -1.5f));

        GLint texture_location1 = glGetUniformLocation(_shader.getShaderID(), "tex_");
        glUniform1i(texture_location1, 0);

        GLint texture_location2 = glGetUniformLocation(_shader.getShaderID(), "nTex");
        glUniform1i(texture_location2, 1);

        GLint modelMatrixLoc = glGetUniformLocation(_shader.getShaderID(), "modelMatrix");
        glUniformMatrix4fv(modelMatrixLoc, 1, false, (float*)&_modelMatrix);
        glBindBuffer(GL_ARRAY_BUFFER, _vboID);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
      }
     
     // face right
//      {
//          _texture->use();
//          _modelMatrix = glm::mat4x4(1.0); 
//          _modelMatrix = glm::translate(_modelMatrix, glm::vec3(0.75f, 0.0f, -3.0f));
//          _modelMatrix = glm::rotate(_modelMatrix, trans, glm::vec3(0.0f, 1.0f, 0.0f));
//          //_modelMatrix = glm::scale(_modelMatrix, glm::vec3(0.2f, 1.0f, 1.0f));
//          
//          //_modelMatrix = glm::transpose(_modelMatrix);
//  
//          GLint texture_location = glGetUniformLocation(_shader.getShaderID(), "tex_");
//          glUniform1i(texture_location, 0);
//  
//          GLint modelMatrixLoc = glGetUniformLocation(_shader.getShaderID(), "modelMatrix");
//          glUniformMatrix4fv(modelMatrixLoc, 1, false, (float*)&_modelMatrix);
//          glBindBuffer(GL_ARRAY_BUFFER, _vboID);
//          glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
//      }
// 
//      // face left
//       {
//          _texture->use();
//          _modelMatrix = glm::mat4x4(1.0); 
//          _modelMatrix = glm::translate(_modelMatrix, glm::vec3(-0.75f, 0.0f, -3.0f));
//          _modelMatrix = glm::rotate(_modelMatrix, trans, glm::vec3(0.0f, 1.0f, 0.0f));
//          //_modelMatrix = glm::scale(_modelMatrix, glm::vec3(0.2f, 1.0f, 1.0f));
// 
//          //_modelMatrix = glm::transpose(_modelMatrix);
// 
//          GLint texture_location = glGetUniformLocation(_shader.getShaderID(), "tex_");
//          glUniform1i(texture_location, 0);
// 
//          GLint modelMatrixLoc = glGetUniformLocation(_shader.getShaderID(), "modelMatrix");
//          glUniformMatrix4fv(modelMatrixLoc, 1, false, (float*)&_modelMatrix);
//          glBindBuffer(GL_ARRAY_BUFFER, _vboID);
//          glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
//       }
// 
//      // face bottom
//      {
//           _texture->use();
//           _modelMatrix = glm::mat4x4(1.0); 
//           _modelMatrix = glm::translate(_modelMatrix, glm::vec3(0.0f, 0.0f, -5.0f));
// 
//           GLint texture_location = glGetUniformLocation(_shader.getShaderID(), "tex_");
//           glUniform1i(texture_location, 0);
// 
//           GLint modelMatrixLoc = glGetUniformLocation(_shader.getShaderID(), "modelMatrix");
//           glUniformMatrix4fv(modelMatrixLoc, 1, false, (float*)&_modelMatrix);
//           glBindBuffer(GL_ARRAY_BUFFER, _vboID);
//           glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
//      }
}

void View::Board::createGeometry()
{
    glGenBuffers(1, &_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    const float boardSize = 0.75f;
    const float depth     = 0.0f;
    GLfloat geometry[] = {
         boardSize, boardSize, depth,
        -boardSize, boardSize, depth,
         boardSize,-boardSize, depth,
         boardSize,-boardSize, depth,
        -boardSize, boardSize, depth,
        -boardSize,-boardSize, depth,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(geometry), geometry, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

View::Board::~Board()
{

}
