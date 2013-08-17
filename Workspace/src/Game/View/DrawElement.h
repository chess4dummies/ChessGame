#ifndef _DRAW_ELEMENT_
#define _DRAW_ELEMENT_

#include "Shader.h"
#include "Texture.h"
#include "src/glm/glm.hpp"
#include "Common.h"

namespace View {

// Abstract base class for all drawables. Pieces inherit from this
class DrawElement
{
public:
    DrawElement();
    DrawElement( const DrawElement& other );
    DrawElement( const ePieceType pieceType, const Position& pos );

    virtual ~DrawElement();
    void operator = ( const DrawElement& other );
    virtual void draw() = 0;
    virtual void createGeometry() = 0;

    
    void updatePosition( const int x, const int y );

    static void init();
    static DrawElement* createDrawElement( const ePieceType piece, const View::Position& pos ); // THIS IS NOT GOOD!!

    void setHighlighted();
    void setUnHighlighted();

    // Used like a hack now.
    void useShader()
    {
        _shader.use();
    }
    const Shader& getShader() const
    {
        return _shader;
    }

    const Position& getPosition() const
    {
        return _position;
    }

    const ePieceType getType() const
    {
        return _pieceType;
    }

protected:
    // Common to everyone. So, putting in base class.
    void checkIfHighlighted();

    static std::string _vertSrcArr[NUM_DRAWELEMS];
    static std::string _fragSrcArr[NUM_DRAWELEMS];

    bool        _isHighlighted;
    Position    _position;
    GLuint      _vboID;
    Shader      _shader;
    ePieceType  _pieceType;
    glm::mat4x4 _modelMatrix; // object coordinates -> world
    std::vector<Texture*>    _textureList; // max 10 :P
};
}

#endif