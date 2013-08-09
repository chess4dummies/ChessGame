#ifndef _DRAW_ELEMENT_
#define _DRAW_ELEMENT_

#include "Shader.h"
#include "Texture.h"

namespace View {

    // Abstract base class for all drawables. Pieces inherit from this
class DrawElement
{
public:
    DrawElement();
    DrawElement( const DrawElement& other );

    enum ePieceType
    {
        QUEEN  = 1,
        ROOK   = 2,
        BISHOP = 3,
        KNIGHT = 4,
        PAWN   = 5,
        KING   = 6,
        BOARD  = 7,
        NUM_DRAWELEMS
    };
    DrawElement( const ePieceType pieceType );

    virtual ~DrawElement();
    void operator = ( const DrawElement& other );
    virtual void draw() = 0;
    virtual void createGeometry() = 0;

    static void init();

protected:
    static std::string _vertSrcArr[NUM_DRAWELEMS];
    static std::string _fragSrcArr[NUM_DRAWELEMS];

    GLuint      _vboID;
    Shader      _shader;
    ePieceType  _pieceType;
    Texture*    _texture;

};
}

#endif