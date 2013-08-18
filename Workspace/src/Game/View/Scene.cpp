#include "Scene.h"
#include <src/glm/gtc/matrix_transform.hpp>
#include "Common.h"
#include "Pieces/Marker.h"

using namespace std;

View::Scene::Scene()
{
    _selectedPiece = NULL;
    _projectionMatrix = glm::transpose( glm::perspective(FOV_Y, ASPECT_RATIO ,1.0f ,100.0f) );

    const View::Position p(1, 1);
    addDrawElement( View::MARKER, p, PLAYER_1 );
}

View::Scene::Scene( const Scene& other )
{

}

View::Scene::~Scene()
{
    // clear all draw elements!
}

void View::Scene::addDrawElement( const View::ePieceType piece, const View::Position& pos, const ePlayer player )
{
    DrawElement* drawElem = DrawElement::createDrawElement(piece, pos);
    drawElem->setPlayer(player);
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


View::PieceInformation View::Scene::getPieceInformation( const int x, const int y )
{
    // @todo: try to remove warning.
    vector< View::DrawElement* >::iterator itr = find_if( _drawElementList.begin()+1, _drawElementList.end(), PieceFunctor(x, y) );
    if ( itr != _drawElementList.end() )
    {
        // we have a valid piece.
        PieceInformation p( (*itr)->getType(), Position(x, y), (*itr)->getPlayer() );
        return p;
    }

    PieceInformation p( MARKER, Position(x, y), PLAYER_1 ); // return marker, and just say it's player 1's
    return p;
}


void View::Scene::setSelectedPiece( const View::PieceInformation& piece )
{ 
    vector< View::DrawElement* >::iterator itr = find_if( _drawElementList.begin()+1, _drawElementList.end(), SelectFunctor(piece) );
    if ( itr != _drawElementList.end() )
    {
        // This is the selected piece.
        _selectedPiece = *itr;
    }
}

void View::Scene::unSelectPiece()
{
    _selectedPiece = NULL;
}

// True if we can move.
bool View::Scene::checkToMove() const
{
    return (_selectedPiece != NULL);
}

void View::Scene::updatePosition( const int x, const int y)
{
    assert(_selectedPiece);
    _selectedPiece->updatePosition(x, y);
    unSelectPiece();
}