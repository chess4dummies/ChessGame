#include "DrawElement.h"
#include "Board.h"
#include "Pieces/Pawn.h"
#include "Pieces/Marker.h"

using namespace View;


std::string View::DrawElement::_fragSrcArr[DrawElement::NUM_DRAWELEMS];
std::string View::DrawElement::_vertSrcArr[DrawElement::NUM_DRAWELEMS];

DrawElement::DrawElement():
_position(0, 0),
_isHighlighted(false)
{

}

DrawElement::DrawElement( const DrawElement& other ):
_position(0, 0),
_isHighlighted(false)
{

}

void DrawElement::operator=( const DrawElement& other )
{

}

DrawElement::~DrawElement()
{

}

DrawElement::DrawElement( const ePieceType pieceType, const Position& pos ):
_shader( _vertSrcArr[pieceType], _fragSrcArr[pieceType] ),
_position(0, 0),
_isHighlighted(false)
{
    _position = pos;
    _shader.init();
    _pieceType = pieceType;
}

void View::DrawElement::init()
{
    /////////////////////////////////////////////////////////////////////////////////////////////////
                                            // BOARD:
    /////////////////////////////////////////////////////////////////////////////////////////////////
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
        "   float nDotL = dot( normalize(col2.xyz), normalize(vec3(1.0, 1.0, 0.0)) );\n"
        "   vec4 lambert = vec4(1.0, 1.0, 1.0, 1.0) * max (nDotL, 0.0);\n"
        "   if (nDotL != 0.0)col = col1 * lambert; else col = col1;\n"
        "}\n";
    ;
    /////////////////////////////////////////////////////////////////////////////////////////////////


    /////////////////////////////////////////////////////////////////////////////////////////////////
                                            // PAWN:
    /////////////////////////////////////////////////////////////////////////////////////////////////
     _vertSrcArr[DrawElement::PAWN] =
        "#version 330\n"
        "layout(location = 0) in vec3 pos;\n"
        "out vec2 texcoord;\n"
        "uniform mat4 modelMatrix;\n"
        "uniform mat4 viewMatrix;\n"
        "uniform mat4 projMatrix;\n"
        "  \n"
        "const vec3 vertData[36] = vec3[]\n"
        "(\n"
        "   vec3( 0.0,  0.0, 0.0),\n"
        "   vec3( 0.0,  1.0, 0.0),\n"
        "   vec3( 1.0,  0.0, 0.0),\n"
        "   vec3( 1.0,  0.0, 0.0),\n"
        "   vec3( 1.0,  1.0, 0.0),\n"
        "   vec3( 0.0,  1.0, 0.0),\n"

        "   vec3( 0.0,  0.0,  0.0),\n"
        "   vec3( 0.0,  0.0, -1.0),\n"
        "   vec3( 1.0,  0.0,  0.0),\n"
        "   vec3( 1.0,  0.0,  0.0),\n"
        "   vec3( 1.0,  0.0, -1.0),\n"
        "   vec3( 0.0,  0.0, -1.0),\n"

        "   vec3( 1.0,  0.0,  0.0),\n"
        "   vec3( 1.0,  1.0,  0.0),\n"
        "   vec3( 1.0,  0.0, -1.0),\n"
        "   vec3( 1.0,  0.0, -1.0),\n"
        "   vec3( 1.0,  1.0, -1.0),\n"
        "   vec3( 1.0,  1.0,  0.0),\n"

        "   vec3( 0.0,  0.0,  0.0),\n"
        "   vec3( 0.0,  1.0, -1.0),\n"
        "   vec3( 0.0,  1.0, -1.0),\n"
        "   vec3( 0.0,  1.0, -1.0),\n"
        "   vec3( 0.0,  1.0,  0.0),\n"
        "   vec3( 0.0,  0.0,  0.0),\n"

        "   vec3( 0.0,  1.0,  0.0),\n"
        "   vec3( 0.0,  1.0, -1.0),\n"
        "   vec3( 1.0,  1.0, -1.0),\n"
        "   vec3( 1.0,  1.0, -1.0),\n"
        "   vec3( 1.0,  1.0,  0.0),\n"
        "   vec3( 0.0,  1.0,  0.0),\n"

        "   vec3( 0.0,  0.0, -1.0),\n"
        "   vec3( 0.0,  1.0, -1.0),\n"
        "   vec3( 1.0,  1.0, -1.0),\n"
        "   vec3( 1.0,  1.0, -1.0),\n"
        "   vec3( 0.0,  0.0, -1.0),\n"
        "   vec3( 1.0,  0.0, -1.0)\n"

        ");\n"
        "  \n"
        "const vec2 data[36] = vec2[]\n"
        "(\n"
        "   vec2( 0.0,  0.0),\n"
        "   vec2( 0.0,  1.0),\n"
        "   vec2( 1.0,  0.0),\n"
        "   vec2( 1.0,  0.0),\n"
        "   vec2( 1.0,  1.0),\n"
        "   vec2( 0.0,  1.0),\n"

        "   vec2( 0.0,  1.0),\n"
        "   vec2( 0.0,  0.0),\n"
        "   vec2( 1.0,  1.0),\n"
        "   vec2( 1.0,  1.0),\n"
        "   vec2( 1.0,  0.0),\n"
        "   vec2( 0.0,  0.0),\n"

        "   vec2( 0.0,  0.0),\n"
        "   vec2( 0.0,  1.0),\n"
        "   vec2( 1.0,  0.0),\n"
        "   vec2( 1.0,  0.0),\n"
        "   vec2( 1.0,  1.0),\n"
        "   vec2( 0.0,  1.0),\n"

        "   vec2( 1.0,  0.0),\n"
        "   vec2( 0.0,  0.0),\n"
        "   vec2( 0.0,  1.0),\n"
        "   vec2( 0.0,  1.0),\n"
        "   vec2( 1.0,  1.0),\n"
        "   vec2( 1.0,  0.0),\n"

        "   vec2( 0.0,  0.0),\n"
        "   vec2( 0.0,  1.0),\n"
        "   vec2( 1.0,  1.0),\n"
        "   vec2( 1.0,  1.0),\n"
        "   vec2( 1.0,  0.0),\n"
        "   vec2( 0.0,  0.0),\n"

        "   vec2( 1.0,  0.0),\n"
        "   vec2( 1.0,  1.0),\n"
        "   vec2( 0.0,  1.0),\n"
        "   vec2( 0.0,  1.0),\n"
        "   vec2( 1.0,  0.0),\n"
        "   vec2( 0.0,  0.0)\n"

        ");\n"
        "void main()\n"
        "{\n"
        "   gl_Position = ( projMatrix * viewMatrix * modelMatrix * vec4(vertData[gl_VertexID], 1.0) );\n"
        "   texcoord = data[gl_VertexID];"
        "}\n";
    ;

    _fragSrcArr[DrawElement::PAWN] = 
        "#version 330\n"
        "layout(location = 0) out vec4 col;\n"
        "in vec2 texcoord;\n"
        "uniform sampler2D tex_;\n"
        "uniform sampler2D nTex;\n"
        "uniform float highlight;\n"
        "void main()"
        "{\n"
        "   vec4 col1 = texture(tex_, texcoord);\n"
        "   vec4 col2 = texture(nTex, texcoord);\n"
        "   float nDotL = dot( normalize(col2.xyz), normalize(vec3(1.0, 1.0, 0.0)) );\n"
        "   vec4 lambert = vec4(1.0, 1.0, 1.0, 1.0) * max (nDotL, 0.0);\n"
        "   col = col1 * lambert * vec4(highlight, highlight, highlight, 1.0);\n"
        "}\n";
    ;
    /////////////////////////////////////////////////////////////////////////////////////////////////


    /////////////////////////////////////////////////////////////////////////////////////////////////
                                            // MARKER:
    /////////////////////////////////////////////////////////////////////////////////////////////////
     _vertSrcArr[DrawElement::MARKER] =
        "#version 330\n"
        "layout(location = 0) in vec3 pos;\n"
        "out vec2 texcoord;\n"
        "uniform mat4 modelMatrix;\n"
        "uniform mat4 viewMatrix;\n"
        "uniform mat4 projMatrix;\n"
        "  \n"
        "const vec3 vertData[36] = vec3[]\n"
        "(\n"
        "   vec3( 0.0,  0.0, 0.0),\n"
        "   vec3( 0.0,  1.0, 0.0),\n"
        "   vec3( 1.0,  0.0, 0.0),\n"
        "   vec3( 1.0,  0.0, 0.0),\n"
        "   vec3( 1.0,  1.0, 0.0),\n"
        "   vec3( 0.0,  1.0, 0.0),\n"

        "   vec3( 0.0,  0.0,  0.0),\n"
        "   vec3( 0.0,  0.0, -1.0),\n"
        "   vec3( 1.0,  0.0,  0.0),\n"
        "   vec3( 1.0,  0.0,  0.0),\n"
        "   vec3( 1.0,  0.0, -1.0),\n"
        "   vec3( 0.0,  0.0, -1.0),\n"

        "   vec3( 1.0,  0.0,  0.0),\n"
        "   vec3( 1.0,  1.0,  0.0),\n"
        "   vec3( 1.0,  0.0, -1.0),\n"
        "   vec3( 1.0,  0.0, -1.0),\n"
        "   vec3( 1.0,  1.0, -1.0),\n"
        "   vec3( 1.0,  1.0,  0.0),\n"

        "   vec3( 0.0,  0.0,  0.0),\n"
        "   vec3( 0.0,  1.0, -1.0),\n"
        "   vec3( 0.0,  1.0, -1.0),\n"
        "   vec3( 0.0,  1.0, -1.0),\n"
        "   vec3( 0.0,  1.0,  0.0),\n"
        "   vec3( 0.0,  0.0,  0.0),\n"

        "   vec3( 0.0,  1.0,  0.0),\n"
        "   vec3( 0.0,  1.0, -1.0),\n"
        "   vec3( 1.0,  1.0, -1.0),\n"
        "   vec3( 1.0,  1.0, -1.0),\n"
        "   vec3( 1.0,  1.0,  0.0),\n"
        "   vec3( 0.0,  1.0,  0.0),\n"

        "   vec3( 0.0,  0.0, -1.0),\n"
        "   vec3( 0.0,  1.0, -1.0),\n"
        "   vec3( 1.0,  1.0, -1.0),\n"
        "   vec3( 1.0,  1.0, -1.0),\n"
        "   vec3( 0.0,  0.0, -1.0),\n"
        "   vec3( 1.0,  0.0, -1.0)\n"

        ");\n"
        "  \n"
        "const vec2 data[6] = vec2[]\n"
        "(\n"
        "   vec2( 0.0,  0.0),\n"
        "   vec2( 0.0,  1.0),\n"
        "   vec2( 1.0,  0.0),\n"
        "   vec2( 1.0,  0.0),\n"
        "   vec2( 1.0,  1.0),\n"
        "   vec2( 0.0,  1.0)\n"

        ");\n"
        "void main()\n"
        "{\n"
        "   gl_Position = ( projMatrix * viewMatrix * modelMatrix * vec4(vertData[gl_VertexID], 1.0) );\n"
        "   texcoord = data[gl_VertexID];"
        "}\n";
    ;

    _fragSrcArr[DrawElement::MARKER] = 
        "#version 330\n"
        "layout(location = 0) out vec4 col;\n"
        "void main()"
        "{\n"
        "   col = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";
    ;
    /////////////////////////////////////////////////////////////////////////////////////////////////
}

DrawElement* View::DrawElement::createDrawElement( const ePieceType piece, const View::Position& pos )
{
    switch (piece)
    {
    case BOARD:
        return new Board(pos);
    case PAWN:
        return new Pawn(pos);
    case MARKER:
        return new Marker(pos);
    }
    return NULL;
}

void View::DrawElement::updatePosition(const int x, const int y)
{
    _position._x = x;
    _position._y = y;
}

void View::DrawElement::setHighlighted()
{
    _isHighlighted = true;
}

void View::DrawElement::setUnHighlighted()
{
    _isHighlighted = false;
}

void View::DrawElement::checkIfHighlighted()
{
    GLfloat highlight = (_isHighlighted) ? HIGHLIGHT_ON : HIGHLIGHT_OFF;
    GLint highlightLoc = glGetUniformLocation(_shader.getShaderID(), "highlight");
    glUniform1f(highlightLoc, highlight);  
}