#include "DrawElement.h"
#include "Board.h"

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
        "out vec2 texcoord;\n"
        "uniform mat4 modelMatrix;\n"
        "uniform mat4 viewMatrix;\n"
        "uniform mat4 projMatrix;\n"
        "const vec2 data[6] = vec2[]\n"
        "(\n"
        "   vec2( 1.0,  1.0),\n"
        "   vec2( 0.0,  1.0),\n"
        "   vec2( 1.0,  0.0),\n"
        "   vec2( 1.0,  0.0),\n"
        "   vec2( 0.0,  1.0),\n"
        "   vec2( 0.0,  0.0)\n"
        ");\n"
        "void main()\n"
        "{\n"
        "   gl_Position = ( projMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0) );\n"
        "   texcoord = data[gl_VertexID];"
        "}\n";
    ;

    _fragSrcArr[DrawElement::BOARD] = 
        "#version 330\n"
        "layout(location = 0) out vec4 col;\n"
        "in vec2 texcoord;\n"
        "uniform sampler2D tex_;\n"
        "uniform sampler2D nTex;\n"
        "void main()"
        "{\n"
        "   vec4 col1 = texture(tex_, texcoord);\n"
        "   vec4 col2 = texture(nTex, texcoord);\n"
        "   float nDotL = dot(col2.xyz, vec3(1.0, 1.0, 0.0));\n"
        "   vec4 lambert = vec4(1.0, 1.0, 1.0, 1.0) * vec4(1.0, 1.0, 1.0, 1.0) * max (nDotL, 0.0);\n"
        "   if (nDotL != 0.0)col = col1 * lambert; else col = col1;\n"
        "}\n";
    ;
}

DrawElement* View::DrawElement::createDrawElement( const ePieceType piece )
{
    switch (piece)
    {
    case BOARD:
        return new Board;
    }
    return NULL;
}

