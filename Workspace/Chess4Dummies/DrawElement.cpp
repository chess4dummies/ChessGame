#include "DrawElement.h"

using namespace View;

std::string View::DrawElement::_fragSrcArr[DrawElement::NUM_DRAWELEMS];
std::string View::DrawElement::_vertSrcArr[DrawElement::NUM_DRAWELEMS];

DrawElement::DrawElement()
{

}

DrawElement::DrawElement( const DrawElement& other )
{

}

void DrawElement::operator=( const DrawElement& other )
{

}

DrawElement::~DrawElement()
{

}

DrawElement::DrawElement( const ePieceType pieceType ):
_shader( _vertSrcArr[DrawElement::BOARD], _fragSrcArr[DrawElement::BOARD] )
{
    _shader.init();
    _pieceType = pieceType;
}

void View::DrawElement::init()
{
    _vertSrcArr[DrawElement::BOARD] =
        "#version 330\n"
        "layout(location = 0) in vec3 pos;\n"
        "void main() {\n"
        " gl_Position = vec4(pos, 1.0);\n"
        "}\n";
    ;

    _fragSrcArr[DrawElement::BOARD] = 
        "#version 330\n"
        "layout(location = 0) out vec4 col;\n"
        "void main() {\n"
        " col = vec4(1.0, 1.0, 0.0, 1.0);\n"
        "}\n";
    ;
}

