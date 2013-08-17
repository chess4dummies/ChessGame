#include "Board.h"
#include <src/glm/gtc/matrix_transform.hpp>


using namespace View;

View::Board::Board( const Position& pos )
:DrawElement( View::BOARD, pos )
{
    _textureList.reserve(MAX_TEXTURES);
    _textureList.resize(MAX_TEXTURES);
    _textureList[0] = new Texture("data/board.bmp");
    _textureList[1] = new Texture("data/board_bump.bmp");
}

static float rot = BOARD_ROT;
void View::Board::draw()
{
#ifdef ROTATION_ON
    rot += 0.25f;
#endif
    //face up
      {
        _textureList[0]->use();
        _textureList[1]->use();

        _modelMatrix = glm::mat4x4(1.0); 
        _modelMatrix = glm::translate(_modelMatrix, glm::vec3(0.0f, 0.0f, BOARD_TRANS));
        _modelMatrix = glm::rotate(_modelMatrix, rot, glm::vec3(1.0f, 0.0f, 0.0f));
        _modelMatrix = glm::scale(_modelMatrix, glm::vec3(BOARD_SCALE));

        GLint texture_location1 = glGetUniformLocation(_shader.getShaderID(), "tex_");
        glUniform1i(texture_location1, _textureList[0]->getGLTexID());

        GLint texture_location2 = glGetUniformLocation(_shader.getShaderID(), "nTex");
        glUniform1i(texture_location2, _textureList[1]->getGLTexID());

        GLint modelMatrixLoc = glGetUniformLocation(_shader.getShaderID(), "modelMatrix");
        glUniformMatrix4fv(modelMatrixLoc, 1, false, (float*)&_modelMatrix);
       
        glBindBuffer(GL_ARRAY_BUFFER, _vboID);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
        glDisableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        _textureList[0]->unUse();
        _textureList[1]->unUse();
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

    const float boardSize = 1.0f;
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

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

View::Board::~Board()
{

}
