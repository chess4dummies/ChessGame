#include "view/DrawElement.h"
#include "view/Board.h"
#include "view/Scene.h"

using namespace View;
bool once = false;

int xPos = 0, yPos = 0;
Scene* scene;

void initShaders()
{
    DrawElement::init();
    scene = new Scene;
    const View::Position p1(0, 0);
    scene->addDrawElement(DrawElement::PAWN, p1 );

    const View::Position p2(4, 4);
    //scene->addDrawElement(DrawElement::PAWN, p2 );
    
    const View::Position p3(1, 5);
    //scene->addDrawElement(DrawElement::PAWN, p3 );    

    for (int i = 0; i < 8; i++)
    {
        const View::Position p4(i, 0);
        scene->addDrawElement(DrawElement::PAWN, p4 ); 
    }    

    scene->highlightPosition(xPos, yPos);
    scene->addDrawElement(DrawElement::BOARD, p3);
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
    default:
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
    initShaders();
    glutMainLoop();
    return 0;
}