#ifndef _COMMON_
#define _COMMON_

#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <functional>

#define TEX_WIDTH  256
#define TEX_HEIGHT 256

#define MAX_TEXTURES 10

// These are just visually "right" things. To be changed as appears right.
#define BOARD_TRANS    -8.0f
#define PIECE_TRANS    -7.96f
#define FOV_Y          25.0f 
#define BOARD_ROT      306.0f
#define BOARD_SCALE    (3.3f * 0.75f), (3.3f * 0.75f), (1.0f * 0.75f)
#define ASPECT_RATIO   1.0f
#define BOARD_SIZE     3.3f * 0.75f
#define PIECE_SIZE     (3.3f * 0.75f * 0.75f) / (4.0f) // 95% of each block
#define PIECE_PLACE    -BOARD_SIZE, -BOARD_SIZE+PIECE_SIZE, BOARD_TRANS/* + PIECE_SIZE*/

#define PIECE_Y_OFFSET (PIECE_SIZE + PIECE_SIZE)
#define PIECE_Z_OFFSET BOARD_TRANS+PIECE_SIZE/2.0f

#define OFF_ST (3.3f * 0.75f / 64.0f)
#define PIECE_OFFSET   (3.3f * 0.75f / 4.0f)


#define HIGHLIGHT_ON     1.0f
#define HIGHLIGHT_OFF    0.5f

//#define ROTATION_ON

// #define  CHECK_GL_ERROR \{
//                         \    GLenum err = glGetError();
//                         \    assert( err == GL_NO_ERROR );
//                         \}

namespace View {

struct Position 
{
    Position( const int x, const int y)
    {
        _x = x;
        _y = y;
    }
    int _x;
    int _y;
};


enum ePieceType
{
    QUEEN  = 1,
    ROOK   = 2,
    BISHOP = 3,
    KNIGHT = 4,
    PAWN   = 5,
    KING   = 6,
    BOARD  = 7,
    MARKER = 8,
    NUM_DRAWELEMS
};


struct PieceInformation
{
    PieceInformation( const ePieceType piece, const Position& pos ):
    _pos(pos._x, pos._y)
    {
        _piece = piece;
    }

    ePieceType _piece;
    Position   _pos;
};

}

#endif
