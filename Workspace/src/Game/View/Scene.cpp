#include "Scene.h"
#include <src/glm/gtc/matrix_transform.hpp>
#include "Common.h"
#include "Pieces/Marker.h"

using namespace std;

View::Scene::Scene()
{
    _projectionMatrix = glm::transpose( glm::perspective(FOV_Y, ASPECT_RATIO ,1.0f ,100.0f) );

    const View::Position p(1, 1);
    addDrawElement( DrawElement::MARKER, p );
}

View::Scene::Scene( const Scene& other )
{

}

View::Scene::~Scene()
{
    // clear all draw elements!
}

void View::Scene::addDrawElement( const DrawElement::ePieceType piece, const View::Position& pos )
{
    DrawElement* drawElem = DrawElement::createDrawElement(piece, pos);
    assert(drawElem);
    drawElem->createGeometry();
    _drawElementList.push_back(drawElem);
}

void View::Scene::removeDrawElement( const glm::vec2& pos )
{

}

void View::Scene::setHighlighting( const DrawElement* dr )
{
    assert(dr);
    if ( dr == _drawElementList[0] ) // don't mark marker :D !
        return;

    if ( (dr->getPosition()._x == _drawElementList[0]->getPosition()._x) && (dr->getPosition()._y == _drawElementList[0]->getPosition()._y) )
    {
        const_cast<DrawElement*>(dr)->setHighlighted(); // HACK? No other way?
    }
    else
    {
        const_cast<DrawElement*>(dr)->setUnHighlighted(); // HACK? No other way?
    }
}

static float trans = 45.0f;
void View::Scene::drawScene()
{
    // TRY THIS!!
    // std::for_each(_drawElementList.begin(), _drawElementList.end(), &View::Scene::drawElements );
    for ( vector<DrawElement*>::iterator itr = _drawElementList.begin();
          itr != _drawElementList.end();
          itr++)
    {
        (*itr)->useShader();
        setHighlighting(*itr);
        
        _viewMatrix = glm::mat4x4(1.0);
        _viewMatrix = glm::rotate(_viewMatrix, -5.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        //_viewMatrix = glm::transpose(_viewMatrix);
        
        GLint viewMatrixLoc = glGetUniformLocation((*itr)->getShader().getShaderID(), "viewMatrix");
        glUniformMatrix4fv(viewMatrixLoc, 1, false, (float*)&_viewMatrix);

        GLint projMatrixLoc = glGetUniformLocation((*itr)->getShader().getShaderID(), "projMatrix");
        glUniformMatrix4fv(projMatrixLoc, 1, false, (float*)&_projectionMatrix);
        (*itr)->draw();
    }
}

void View::Scene::rotateScene( const float rad, const glm::vec3& axis )
{
    _viewMatrix = glm::rotate(_viewMatrix, rad, axis);
}

void View::Scene::highlightPosition( const int x, const int y )
{
    // Update to (x, y)
    _drawElementList[0]->updatePosition(x, y); // DE[0] is always marker!
}