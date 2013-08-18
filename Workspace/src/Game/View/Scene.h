#ifndef _SCENE_
#define _SCENE_

#include "Common.h"
#include "DrawElement.h"
#include "src/glm/glm.hpp"

namespace View {

class Scene {
public:
    Scene();
   ~Scene();
    Scene( const Scene& other );

    void addDrawElement( const View::ePieceType piece, const View::Position& pos, const ePlayer player );
    void removeDrawElement( const glm::vec2& pos );
    void drawScene(); // set up matrices, call draw on all elements.

    void rotateScene( const float rad, const glm::vec3& axis );
    void drawElements( DrawElement* d) const;

    void highlightPosition( const int x, const int y );

    PieceInformation getPieceInformation( const int x, const int y );

    // Set the piece as selected. This needs to be moved.
    void setSelectedPiece( const View::PieceInformation& piece ); 
    void unSelectPiece();

    // Doing controller stuff here! Move this out!
    bool checkToMove() const;

    void updatePosition( const int x, const int y );

    // =======================================================================
    //  Functors used with std::find_if. Where to move these to?
    class PieceFunctor
    {
    public:
        PieceFunctor(int x, int y)
        {
            _x = x;
            _y = y;
        }

        bool operator() (const DrawElement* dr)
        {
            return (dr->getPosition()._x == _x) && (dr->getPosition()._y == _y);
        }

    private:
        int _x;
        int _y;
    };

    class SelectFunctor
    {
    public:
        SelectFunctor(const View::PieceInformation& piece):            
        _piece(piece)
        {
            
        }

        bool operator() (const DrawElement* dr)
        {
            return    (dr->getType() == _piece._piece) && (dr->getPlayer() == _piece._player) 
                   && (dr->getPosition()._x == _piece._pos._x)
                   && (dr->getPosition()._y == _piece._pos._y);
        }

    private:
        PieceInformation _piece;
    };
    // =======================================================================    

private:
    void operator = ( const Scene& other ); // non-copyable
    void setHighlighting( const DrawElement* dr );
    
    DrawElement* _selectedPiece;   // A reference to the piece;
    DrawElement* _marker;          // marker separate from DE list
    glm::mat4x4  _viewMatrix;      // world  -> camera
    glm::mat4x4  _projectionMatrix;// camera -> clip
    std::vector< View::DrawElement* > _drawElementList;
};

}
#endif