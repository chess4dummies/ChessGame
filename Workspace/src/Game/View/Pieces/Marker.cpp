#include "Marker.h"
#include <src/glm/gtc/matrix_transform.hpp>


using namespace View;

View::Marker::Marker( const View::Position& pos )
:DrawElement( DrawElement::MARKER, pos )
{
}

static float rot = BOARD_ROT;
void View::Marker::draw()
{
#ifdef ROTATION_ON
    rot += 0.25f;
    std::cout << rot << std::endl;
#endif
               
    // @todo:
    // Some dirty calculations here!
    {
        _modelMatrix = glm::mat4x4(1.0); 
        _modelMatrix = glm::translate( _modelMatrix, glm::vec3(0.0f, 0.0f, BOARD_TRANS+0.1f) ); // Slight offset to avoid Z fights
        _modelMatrix = glm::rotate(_modelMatrix, rot, glm::vec3(1.0f, 0.0f, 0.0f));    
        _modelMatrix = glm::translate( _modelMatrix, glm::vec3(PIECE_OFFSET * (_position._x), PIECE_OFFSET * _position._y, 0.0f) ); 
        _modelMatrix = glm::translate( _modelMatrix, glm::vec3(-BOARD_SIZE + PIECE_SIZE, -BOARD_SIZE + PIECE_SIZE, 0.0f) );                 
        _modelMatrix = glm::scale(_modelMatrix, glm::vec3(PIECE_SIZE, PIECE_SIZE, 0.0f));
        _modelMatrix = glm::translate( _modelMatrix, glm::vec3(-0.5, -0.5f, 0.5f) );
    }

    GLint modelMatrixLoc = glGetUniformLocation(_shader.getShaderID(), "modelMatrix");
    glUniformMatrix4fv(modelMatrixLoc, 1, false, (float*)&_modelMatrix);        
        
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void View::Marker::createGeometry()
{
    glGenBuffers(1, &_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    // not used!
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

View::Marker::~Marker()
{

}
