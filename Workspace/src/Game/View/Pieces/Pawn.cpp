#include "Pawn.h"
#include <src/glm/gtc/matrix_transform.hpp>


using namespace View;

View::Pawn::Pawn()
:DrawElement( DrawElement::PAWN )
{
    _textureList.reserve(MAX_TEXTURES);
    _textureList.resize(MAX_TEXTURES);
    _textureList[0] = new Texture("data/pawn.bmp");
    _textureList[1] = new Texture("data/board_bump.bmp");
}

static float trans = 90.0f;
void View::Pawn::draw()
{
    trans += 1.5f;
    //face up
      {
        _textureList[0]->use();
        _textureList[1]->use();

        _modelMatrix = glm::mat4x4(1.0); 
        _modelMatrix = glm::translate(_modelMatrix, glm::vec3(0.0f, 0.0f, -2.0f)/*PIECE_TRANS + PIECE_SIZE)*/);
        _modelMatrix = glm::rotate(_modelMatrix, trans, glm::vec3(1.0f, 0.0f, 0.0f));
        _modelMatrix = glm::scale(_modelMatrix, glm::vec3(PIECE_SIZE, PIECE_SIZE, PIECE_SIZE));

        GLint texture_location1 = glGetUniformLocation(_shader.getShaderID(), "tex_");
        glUniform1i(texture_location1, _textureList[0]->getGLTexID());

        GLint texture_location2 = glGetUniformLocation(_shader.getShaderID(), "nTex");
        glUniform1i(texture_location2, _textureList[1]->getGLTexID());

        GLint modelMatrixLoc = glGetUniformLocation(_shader.getShaderID(), "modelMatrix");
        glUniformMatrix4fv(modelMatrixLoc, 1, false, (float*)&_modelMatrix);        
        
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, _vboID);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDisableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        _textureList[0]->unUse();
        _textureList[1]->unUse();
      }
#if 0  
      // face down
      {
        _modelMatrix = glm::mat4x4(1.0); 
        _modelMatrix = glm::translate(_modelMatrix, glm::vec3(0.0f, 0.0f, PIECE_TRANS - PIECE_SIZE));
        _modelMatrix = glm::rotate(_modelMatrix, trans, glm::vec3(1.0f, 0.0f, 0.0f));
        _modelMatrix = glm::scale(_modelMatrix, glm::vec3(PIECE_SIZE, PIECE_SIZE, 1.0f));

        GLint texture_location1 = glGetUniformLocation(_shader.getShaderID(), "tex_");
        glUniform1i(texture_location1, 0);

        GLint texture_location2 = glGetUniformLocation(_shader.getShaderID(), "nTex");
        glUniform1i(texture_location2, 1);

        GLint modelMatrixLoc = glGetUniformLocation(_shader.getShaderID(), "modelMatrix");
        glUniformMatrix4fv(modelMatrixLoc, 1, false, (float*)&_modelMatrix);        
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, _vboID);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
        glDisableVertexAttribArray(0);
      }
   
     // face right
      {          
          _modelMatrix = glm::mat4x4(1.0); 
          _modelMatrix = glm::translate(_modelMatrix, glm::vec3(PIECE_SIZE, 0.0f, PIECE_TRANS - PIECE_SIZE / 2.0f ));
          _modelMatrix = glm::rotate(_modelMatrix, trans, glm::vec3(1.0f, 0.0f, 0.0f));
          _modelMatrix = glm::rotate(_modelMatrix, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
          _modelMatrix = glm::scale(_modelMatrix, glm::vec3(PIECE_SIZE, PIECE_SIZE, 1.0f));
          
          //_modelMatrix = glm::transpose(_modelMatrix);
  
          GLint texture_location = glGetUniformLocation(_shader.getShaderID(), "tex_");
          glUniform1i(texture_location, 0);
  
          GLint modelMatrixLoc = glGetUniformLocation(_shader.getShaderID(), "modelMatrix");
          glUniformMatrix4fv(modelMatrixLoc, 1, false, (float*)&_modelMatrix);
          glBindBuffer(GL_ARRAY_BUFFER, _vboID);
          glEnableVertexAttribArray(0);
          glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
          glDisableVertexAttribArray(0);
      }
 
       // face left
       {
           _modelMatrix = glm::mat4x4(1.0); 
          _modelMatrix = glm::translate(_modelMatrix, glm::vec3(-PIECE_SIZE, 0.0f, PIECE_TRANS - PIECE_SIZE / 2.0f));
          _modelMatrix = glm::rotate(_modelMatrix, trans, glm::vec3(1.0f, 0.0f, 0.0f));
          _modelMatrix = glm::rotate(_modelMatrix, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
          _modelMatrix = glm::scale(_modelMatrix, glm::vec3(PIECE_SIZE, PIECE_SIZE, 1.0f));
          
          //_modelMatrix = glm::transpose(_modelMatrix);
  
          GLint texture_location = glGetUniformLocation(_shader.getShaderID(), "tex_");
          glUniform1i(texture_location, 0);
  
          GLint modelMatrixLoc = glGetUniformLocation(_shader.getShaderID(), "modelMatrix");
          glUniformMatrix4fv(modelMatrixLoc, 1, false, (float*)&_modelMatrix);
          glBindBuffer(GL_ARRAY_BUFFER, _vboID);
          glEnableVertexAttribArray(0);
          glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
          glDisableVertexAttribArray(0);
       }

      // face bottom
      {
           _modelMatrix = glm::mat4x4(1.0); 
           _modelMatrix = glm::translate(_modelMatrix, glm::vec3(0.0f, 0.0f, -5.0f));
 
           GLint texture_location = glGetUniformLocation(_shader.getShaderID(), "tex_");
           glUniform1i(texture_location, 0);
 
           GLint modelMatrixLoc = glGetUniformLocation(_shader.getShaderID(), "modelMatrix");
           glUniformMatrix4fv(modelMatrixLoc, 1, false, (float*)&_modelMatrix);
           glBindBuffer(GL_ARRAY_BUFFER, _vboID);
           glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
      }

      {
          _modelMatrix = glm::mat4x4(1.0); 
          _modelMatrix = glm::translate(_modelMatrix, glm::vec3(0.0f, 0.0f, PIECE_TRANS-PIECE_SIZE));
          _modelMatrix = glm::rotate(_modelMatrix, BOARD_ROT, glm::vec3(1.0f, 0.0f, 0.0f));
          _modelMatrix = glm::scale(_modelMatrix, glm::vec3(PIECE_SIZE, PIECE_SIZE, 1.0f));
        
          GLint texture_location = glGetUniformLocation(_shader.getShaderID(), "tex_");
          glUniform1i(texture_location, 0);
 
          GLint modelMatrixLoc = glGetUniformLocation(_shader.getShaderID(), "modelMatrix");
          glUniformMatrix4fv(modelMatrixLoc, 1, false, (float*)&_modelMatrix);
          glBindBuffer(GL_ARRAY_BUFFER, _vboID);
          glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
      }
#endif
}

void View::Pawn::createGeometry()
{
    glGenBuffers(1, &_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    const float depth = 0.0f;
    const float ps    = 1000.0f; 
    GLfloat geometry[] = {
         ps, ps, depth,
        -ps, ps, depth,
         ps,-ps, depth,
         ps,-ps, depth,
        -ps, ps, depth,
        -ps,-ps, depth,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(geometry), geometry, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
}

View::Pawn::~Pawn()
{

}
