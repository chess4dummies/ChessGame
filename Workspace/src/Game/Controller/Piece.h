#ifndef __C_PIECE__
#define __C_PIECE__


#include "View/Common.h"

// After every move, every piece updates its set of valid positions.
// We then check if the move was made to the valid position.
// If that is the case, the update the scene for that particular piece.
// Not sure if this is model's or controller's job.
namespace Controller {

class Piece 
{
public:
    Piece();
    ~Piece();

    void updatePiecePosition( const Position& pos ); // here we validate and update

protected:
    void updateValidPositions(); // Every child will update his valid positions after every "move"

    std::vector< Position > _validPositions; // Where all i can go.
    Position                _position;      
};

}

#endif