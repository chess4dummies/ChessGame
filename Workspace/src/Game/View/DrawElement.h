#ifndef _DRAW_ELEMENT_
#define _DRAW_ELEMENT_

#include "Shader.h"
#include "Texture.h"
#include "src/glm/glm.hpp"
#include "Common.h"

namespace View {

// Offsets from board origin.
struct Position 
{
    Position(int x, int y)
    {
        _x = x;
        _y = y;
    }
    int _x;
    int _y;
};

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
    DrawElement( const ePieceType pieceType, const Position& pos );

    virtual ~DrawElement();
    void operator = ( const DrawElement& other );
    virtual void draw() = 0;
    virtual void createGeometry() = 0;

    static void init();
    static DrawElement* createDrawElement( const ePieceType piece, const View::Position& pos ); // THIS IS NOT GOOD!!


    // Used like a hack now.
    void useShader()
    {
        _shader.use();
    }
    const Shader& getShader() const
    {
        return _shader;
    }

protected:
    static std::string _vertSrcArr[NUM_DRAWELEMS];
    static std::string _fragSrcArr[NUM_DRAWELEMS];

    Position    _position;
    GLuint      _vboID;
    Shader      _shader;
    ePieceType  _pieceType;
    glm::mat4x4 _modelMatrix; // object coordinates -> world
    std::vector<Texture*>    _textureList; // max 10 :P
};
}

#endif