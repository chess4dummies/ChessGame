#include "view/DrawElement.h"
#include "view/Board.h"
#include "view/Scene.h"

using namespace View;
bool once = false;

//////////////////////////////////////////////////////////////////////////////////////
////////////////// Global Data. Only for experimenting and testing! //////////////////
std::string strList[] = 
{
    "INVALID", // the marker. we don't pick it. So, adding dummy here.
    "QUEEN",
    "ROOK",
    "BISHOP",
    "KNIGHT",
    "PAWN",
    "KING" 
};

int xPos = 0, yPos = 0;
Scene* scene;
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


void makeBoard()
{
    DrawElement::init();
    scene = new Scene;

    const View::Position p2(4, 4);
    //scene->addDrawElement(DrawElement::PAWN, p2 );
    
    const View::Position p3(1, 5);
    //scene->addDrawElement(DrawElement::PAWN, p3 );    

    // Player 1
    for (int player = 0; player < NUM_PLAYERS; player++)
    {
        int pos = player == 0 ? 1 : 6;        
        for (int i = 0; i < 8; i++)
        {
            const View::Position p(i, pos);
            scene->addDrawElement(View::PAWN, p ); 
        }

        pos = (player == 0) ? (pos-1) : (pos+1);
        const View::Position pRook1(0, pos);
        scene->addDrawElement(View::ROOK, pRook1 );        
        const View::Position pRook2(7, pos);
        scene->addDrawElement(View::ROOK, pRook2 );

        const View::Position pKnight1(1, pos);
        scene->addDrawElement(View::KNIGHT, pKnight1 );        
        const View::Position pKnight2(6, pos);
        scene->addDrawElement(View::KNIGHT, pKnight2 );

        const View::Position pBishop1(2, pos);
        scene->addDrawElement(View::BISHOP, pBishop1 );        
        const View::Position pBishop2(5, pos);
        scene->addDrawElement(View::BISHOP, pBishop2 );

        const View::Position pKing(4, pos);
        scene->addDrawElement(View::KING, pKing );
        
        const View::Position pQueen(3, pos);
        scene->addDrawElement(View::QUEEN, pQueen );
    }

    scene->highlightPosition(xPos, yPos); // Marker
    scene->addDrawElement(View::BOARD, p3);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene->drawScene();
    glutSwapBuffers();
}

void glInitialisations()
{
    glClearColor(1.0, 1.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    //glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
    //glDisable(GL_DEPTH_TEST); //??
    glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
}
void idle()
{
    // no freeze. continuously render.
    glutPostRedisplay();
}

void keyb( unsigned char c, int , int )
{
    switch (c) 
    {
    case 'a':
        xPos = xPos == 0 ? 8 : xPos;
        xPos = (xPos - 1) % 8;
        break;
    case 'd':
        xPos = (xPos + 1) % 8;
        break;
    case 'w':
        yPos = (yPos + 1) % 8;
        break;
    case 's':
        yPos = yPos == 0 ? 8 : yPos;
        yPos = (yPos - 1) % 8;
        break;
    case 't':
        PieceInformation p( scene->getPieceInformation( xPos, yPos ) );
        std::cout << "Selected: " << strList[p._piece] << std::endl;
        break;
    }
    scene->highlightPosition(xPos, yPos);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("Chess4Dummies");

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyb);

    if (glewInit())
    {
        assert(0);
        return 1;
    }

    glInitialisations();
    makeBoard();
    glutMainLoop();
    return 0;
}